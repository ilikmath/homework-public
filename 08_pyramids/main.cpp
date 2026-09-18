// 212-Терский-Илья-Задача(пирамиды на 2D-плоскости)

#include <fstream>      // библиотека работы с файлами
#include <iomanip>      // форматирование вывода: setw, setprecision
#include <iostream>     // библиотека вывода в консоль
#include <string>       // строки

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>    // переключение консоли в UTF-8, иначе русский текст не читается
#endif

using namespace std;

namespace {

const float pi = 3.14159265f;

const char* const data_filename = "data.txt";

}

// Точка: две координаты на плоскости. Поля закрыты, доступ через get/set.
class Point {
private:
    float x = 0.0f;
    float y = 0.0f;

public:
    Point() = default;
    Point(float x_value, float y_value) : x(x_value), y(y_value) {}

    float getX() const { return x; }
    float getY() const { return y; }

    void setX(float value) { x = value; }
    void setY(float value) { y = value; }
};

// Круг наследует точку и добавляет радиус. Площадь — вычисляемый атрибут,
// то есть метод, а не хранимое поле.
class Circle : public Point {
private:
    float r = 0.0f;

public:
    Circle() = default;
    Circle(float x_value, float y_value, float radius) : Point(x_value, y_value), r(radius) {}

    float getR() const { return r; }
    void setR(float value) { r = value; }

    float area() const { return pi * r * r; }
};

// Пирамида (конус с круглым основанием) наследует круг и добавляет высоту.
// Объём тоже вычисляется, а не хранится.
class Pyramid : public Circle {
private:
    float h = 0.0f;

public:
    Pyramid() = default;
    Pyramid(float x_value, float y_value, float radius, float height)
        : Circle(x_value, y_value, radius), h(height) {}

    float getH() const { return h; }
    void setH(float value) { h = value; }

    float volume() const { return area() * h / 3.0f; }
};

// Поле — площадка с ограничениями по x и y.
class Field {
private:
    float x_min = 0.0f;
    float x_max = 0.0f;
    float y_min = 0.0f;
    float y_max = 0.0f;

public:
    Field(float x_low, float x_high, float y_low, float y_high)
        : x_min(x_low), x_max(x_high), y_min(y_low), y_max(y_high) {}

    float getXmin() const { return x_min; }
    float getXmax() const { return x_max; }
    float getYmin() const { return y_min; }
    float getYmax() const { return y_max; }

    void setXmin(float value) { x_min = value; }
    void setXmax(float value) { x_max = value; }
    void setYmin(float value) { y_min = value; }
    void setYmax(float value) { y_max = value; }

    // Основание должно целиком помещаться в границы площадки.
    bool contains(const Circle& circle) const {
        return circle.getX() - circle.getR() >= x_min && circle.getX() + circle.getR() <= x_max &&
               circle.getY() - circle.getR() >= y_min && circle.getY() + circle.getR() <= y_max;
    }
};

namespace {

// В UTF-8 русская буква занимает два байта, а setw отсчитывает именно байты,
// поэтому кириллический заголовок разъехался бы. Считаем видимые символы сами:
// у продолжающих байтов UTF-8 два старших бита равны 10, их и пропускаем.
string column(const string& text, int width) {
    int visible = 0;

    for (char symbol : text) {
        if ((static_cast<unsigned char>(symbol) & 0xC0) != 0x80) {
            ++visible;
        }
    }

    const int padding = width > visible ? width - visible : 0;

    return string(static_cast<size_t>(padding), ' ') + text;
}

void print_header() {
    cout << fixed << setprecision(3);
    cout << column("N", 4) << column("x", 10) << column("y", 10) << column("R", 10)
         << column("H", 10) << column("площадь", 12) << column("объём", 12) << endl;
}

void print_pyramid(int number, const Pyramid& pyramid) {
    cout << setw(4) << number << setw(10) << pyramid.getX() << setw(10) << pyramid.getY()
         << setw(10) << pyramid.getR() << setw(10) << pyramid.getH() << setw(12)
         << pyramid.area() << setw(12) << pyramid.volume() << endl;
}

// Чтение свойств пирамид из файла: четыре числа в строке — x, y, R, H.
// Каждая прочитанная четвёрка сразу превращается в объект.
// В список объекты пока не складываем — это задание следующей недели.
int create_pyramids(const string& filename, const Field& field) {
    ifstream input(filename);

    if (!input) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return 0;
    }

    float x = 0.0f;
    float y = 0.0f;
    float r = 0.0f;
    float h = 0.0f;
    int line_number = 0;
    int created = 0;

    print_header();

    while (input >> x >> y >> r >> h) {
        ++line_number;

        if (r <= 0.0f || h <= 0.0f) {
            cerr << "Внимание: строка " << line_number
                 << " пропущена, радиус и высота должны быть положительными" << endl;
            continue;
        }

        const Pyramid pyramid(x, y, r, h);

        if (!field.contains(pyramid)) {
            cerr << "Внимание: строка " << line_number
                 << " пропущена, пирамида не помещается в поле" << endl;
            continue;
        }

        ++created;
        print_pyramid(created, pyramid);
    }

    if (!input.eof()) {
        cerr << "Внимание: файл обрывается неполной строкой" << endl;
    }

    return created;
}

}

int main() {
#ifdef _WIN32
    // Исходник в UTF-8, а консоль Windows по умолчанию в другой кодировке:
    // без этой строки вместо русского текста будут кракозябры.
    SetConsoleOutputCP(CP_UTF8);
#endif

    const Field field(-10.0f, 10.0f, -10.0f, 10.0f);

    const int created = create_pyramids(data_filename, field);

    if (created == 0) {
        cerr << "Ошибка: не создано ни одной пирамиды" << endl;
        return 1;
    }

    cout << "Создано пирамид: " << created << endl;

    return 0;
}
