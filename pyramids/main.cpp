// 212-Терский-Илья-Задача(пирамиды на 2D-плоскости)

#include <cmath>        // математические функции: cos, sin, lround
#include <cstdlib>      // strtof: порог из командной строки
#include <fstream>      // библиотека работы с файлами
#include <iomanip>      // форматирование вывода: setw, setprecision
#include <iostream>     // библиотека вывода в консоль
#include <list>         // двунаправленный список STL
#include <random>       // генератор нормально распределённых точек
#include <string>       // строки
#include <vector>       // массивы точек

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>    // переключение консоли в UTF-8, иначе русский текст не читается
#endif

#include "clusters.h"
#include "shapes.h"

using namespace std;

namespace {

const float points_per_volume = 30.0f;  // сколько точек на единицу объёма пирамиды
const float default_threshold = 0.5f;   // порог D: точки ближе D соединяю ребром, можно передать аргументом
const int big_cluster = 10;             // кластер меньше 10 точек считаю выбросом с хвоста Гаусса
const int segments = 72;                // сколько точек в окружности, когда рисую основание
const unsigned int seed = 212u;         // одно и то же зерно, чтобы картинка не менялась от запуска к запуску

const char* const data_filename = "data.txt";
const char* const points_filename = "points.dat";
const char* const bases_filename = "bases.dat";
const char* const squares_filename = "squares.dat";
const char* const clusters_filename = "clusters.txt";
const char* const grid_filename = "grid.gp";

string column(const string& text, int width) {  // setw считает байты, а русская буква — 2 байта, поэтому считаю сам
    int visible = 0;

    for (char symbol : text) {
        if ((static_cast<unsigned char>(symbol) & 0xC0) != 0x80) {  // байты-продолжения UTF-8 (10xxxxxx) не считаю
            ++visible;
        }
    }

    const int padding = width > visible ? width - visible : 0;

    return string(static_cast<size_t>(padding), ' ') + text;
}

list<Pyramid> read_pyramids(const string& filename, const Field& field) {  // читаю x, y, R, H и сразу кладу пирамиду в список
    list<Pyramid> pyramids;
    ifstream input(filename);

    if (!input) {
        cerr << "Ошибка: не удалось открыть файл " << filename << endl;
        return pyramids;
    }

    float x = 0.0f;
    float y = 0.0f;
    float r = 0.0f;
    float h = 0.0f;
    int line_number = 0;

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

        pyramids.push_back(pyramid);
    }

    if (!input.eof()) {
        cerr << "Внимание: файл обрывается неполной строкой" << endl;
    }

    return pyramids;
}

vector<SecondaryPoint> generate_points(const list<Pyramid>& pyramids, const Field& field) {  // под каждой пирамидой облако Гаусса, σ = R / 2
    vector<SecondaryPoint> points;
    mt19937 generator(seed);

    cout << endl << "Вторичные точки (σ = R / 2):" << endl;
    cout << column("N", 4) << column("σ", 10) << column("точек", 10) << column("в круге", 12)
         << endl;

    int number = 0;
    for (const Pyramid& pyramid : pyramids) {
        ++number;
        const float sigma = pyramid.getR() / 2.0f;  // круг основания = 2σ, внутрь попадает примерно 86% точек
        normal_distribution<float> offset(0.0f, sigma);
        const long count = max(1L, lround(pyramid.volume() * points_per_volume));  // чем больше объём, тем больше точек
        int inside = 0;

        for (long k = 0; k < count; ++k) {
            const float dx = offset(generator);
            const float dy = offset(generator);
            const float x = pyramid.getX() + dx;
            const float y = pyramid.getY() + dy;

            if (!field.contains(x, y)) {
                continue;  // точка улетела за поле
            }

            if (dx * dx + dy * dy <= pyramid.getR() * pyramid.getR()) {
                ++inside;
            }
            points.push_back({x, y, number});
        }

        cout << setw(4) << number << setw(10) << sigma << setw(10) << count << setw(11)
             << 100.0f * static_cast<float>(inside) / static_cast<float>(count) << '%' << endl;
    }

    return points;
}

void print_table(const list<Pyramid>& pyramids) {  // таблица пирамид в консоль
    cout << fixed << setprecision(3);
    cout << column("N", 4) << column("x", 10) << column("y", 10) << column("R", 10)
         << column("H", 10) << column("площадь", 12) << column("объём", 12) << endl;

    int number = 0;
    for (const Pyramid& pyramid : pyramids) {
        cout << setw(4) << ++number << setw(10) << pyramid.getX() << setw(10) << pyramid.getY()
             << setw(10) << pyramid.getR() << setw(10) << pyramid.getH() << setw(12)
             << pyramid.area() << setw(12) << pyramid.volume() << endl;
    }
}

void write_bases(const list<Pyramid>& pyramids, const string& filename) {  // окружности оснований для gnuplot
    ofstream output(filename);
    output << fixed << setprecision(4);

    for (const Pyramid& pyramid : pyramids) {
        for (int j = 0; j <= segments; ++j) {
            const float angle =
                2.0f * shapes::pi * static_cast<float>(j) / static_cast<float>(segments);
            output << pyramid.getX() + pyramid.getR() * cos(angle) << ' '
                   << pyramid.getY() + pyramid.getR() * sin(angle) << '\n';
        }

        output << "\n\n";
    }
}

int write_squares(const SquareGrid& grid, const string& filename) {  // непустые квадраты: столбец, строка, угол, сколько точек
    ofstream(grid_filename) << "side = " << grid.side() << '\n';  // сторону квадрата отдаю gnuplot отдельным файлом

    ofstream output(filename);
    output << fixed << setprecision(4);
    output << "# столбец строка x0 y0 точек\n";

    int non_empty = 0;
    for (int row = 0; row < grid.rows(); ++row) {
        for (int col = 0; col < grid.columns(); ++col) {
            const int square = grid.cell(col, row);
            const int count = grid.last(square) - grid.first(square);
            if (count > 0) {
                ++non_empty;
                output << col << ' ' << row << ' ' << grid.cornerX(col) << ' ' << grid.cornerY(row)
                       << ' ' << count << '\n';
            }
        }
    }

    return non_empty;
}

void write_points(const vector<SecondaryPoint>& points, const WaveResult& result,
                  const string& filename) {  // x, y, кластер, цвет; большие кластеры получают цвета 1, 2, 3..., выбросы — 0
    vector<int> size(static_cast<size_t>(result.clusters) + 1, 0);
    for (int id : result.cluster) {
        ++size[static_cast<size_t>(id)];
    }

    vector<int> color(size.size(), 0);
    int next_color = 0;
    for (size_t id = 1; id < size.size(); ++id) {
        if (size[id] >= big_cluster) {
            color[id] = ++next_color;
        }
    }

    ofstream output(filename);
    output << fixed << setprecision(4);

    for (size_t i = 0; i < points.size(); ++i) {
        const size_t id = static_cast<size_t>(result.cluster[i]);
        output << points[i].x << ' ' << points[i].y << ' ' << id << ' ' << color[id] << '\n';
    }
}

int write_clusters(const vector<SecondaryPoint>& points, const WaveResult& result,
                   int pyramid_count, const string& filename) {  // список кластеров, под каждым его точки; возвращает число больших
    vector<vector<int>> members(static_cast<size_t>(result.clusters) + 1);
    for (size_t i = 0; i < points.size(); ++i) {
        members[static_cast<size_t>(result.cluster[i])].push_back(static_cast<int>(i));
    }

    ofstream output(filename);
    output << fixed << setprecision(4);
    int big = 0;

    cout << endl << "Крупные кластеры (от " << big_cluster << " точек):" << endl;
    cout << column("кластер", 9) << column("точек", 8) << column("пирамида", 10)
         << column("доля", 8) << column("шагов", 8) << endl;

    for (int id = 1; id <= result.clusters; ++id) {
        const vector<int>& cluster = members[static_cast<size_t>(id)];

        vector<int> from(static_cast<size_t>(pyramid_count) + 1, 0);  // сколько точек кластера из-под каждой пирамиды
        int steps = 0;                                                // сколько шагов шла волна
        for (int i : cluster) {
            ++from[static_cast<size_t>(points[static_cast<size_t>(i)].source)];
            steps = max(steps, result.wave[static_cast<size_t>(i)]);
        }
        int source = 1;
        for (int p = 2; p <= pyramid_count; ++p) {
            if (from[static_cast<size_t>(p)] > from[static_cast<size_t>(source)]) {
                source = p;
            }
        }
        const float share = static_cast<float>(from[static_cast<size_t>(source)]) /
                            static_cast<float>(cluster.size());

        output << "Кластер " << id << ": " << cluster.size() << " точек, пирамида " << source
               << ", волна шла " << steps << " шагов\n";
        for (int i : cluster) {
            const SecondaryPoint& point = points[static_cast<size_t>(i)];
            output << "  " << i << ' ' << point.x << ' ' << point.y << " шаг "
                   << result.wave[static_cast<size_t>(i)] << '\n';
        }

        if (static_cast<int>(cluster.size()) >= big_cluster) {
            ++big;
            cout << setw(9) << id << setw(8) << cluster.size() << setw(10) << source << setw(7)
                 << setprecision(1) << 100.0f * share << '%' << setw(8) << steps << endl
                 << setprecision(3);
        }
    }

    return big;
}

}  // namespace

int main(int argc, char* argv[]) {
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);  // исходник в UTF-8, без этого в консоли Windows будут кракозябры
#endif

    const float threshold = argc > 1 ? strtof(argv[1], nullptr) : default_threshold;
    if (threshold <= 0.0f) {
        cerr << "Ошибка: порог D должен быть положительным числом" << endl;
        return 1;
    }

    const Field field(-10.0f, 10.0f, -10.0f, 10.0f);

    list<Pyramid> pyramids = read_pyramids(data_filename, field);

    if (pyramids.empty()) {
        cerr << "Ошибка: не создано ни одной пирамиды" << endl;
        return 1;
    }

    pyramids.sort([](const Pyramid& a, const Pyramid& b) { return a.volume() < b.volume(); });  // у списка свой sort, std::sort для него не работает

    cout << "Прочитано пирамид: " << pyramids.size() << ", упорядочены по объёму" << endl;
    print_table(pyramids);

    const vector<SecondaryPoint> points = generate_points(pyramids, field);

    const SquareGrid grid(points, threshold, field.getXmin(), field.getYmin(), field.getXmax(),
                          field.getYmax());  // сторона квадрата = порог, тогда соседи точки только в 9 квадратах вокруг
    const int squares = write_squares(grid, squares_filename);

    const BitMatrix adjacency = buildAdjacency(points, grid, threshold);
    const WaveResult result = runWave(adjacency);

    cout << endl
         << "Точек: " << points.size() << ", порог D = " << threshold << ", квадратов "
         << grid.columns() << "×" << grid.rows() << ", непустых: " << squares << endl;

    const int big = write_clusters(points, result, static_cast<int>(pyramids.size()),
                                   clusters_filename);
    cout << "Всего кластеров: " << result.clusters << ", крупных: " << big
         << ", остальные — выбросы на хвостах" << endl;

    write_points(points, result, points_filename);
    write_bases(pyramids, bases_filename);

    cout << endl
         << "Записаны: " << points_filename << ", " << bases_filename << ", "
         << squares_filename << ", " << grid_filename << ", " << clusters_filename << endl;
    cout << "Рисунок: gnuplot -p plot.gp" << endl;

    return 0;
}
