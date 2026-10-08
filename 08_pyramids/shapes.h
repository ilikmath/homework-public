// 212-Терский-Илья-Задача(пирамиды на 2D-плоскости): классы фигур

#pragma once

namespace shapes {

const float pi = 3.14159265f;

}

class Point {  // точка: просто x и y, поля закрыты, доступ через get/set
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

class Circle : public Point {  // круг = точка-центр + радиус
private:
    float r = 0.0f;

public:
    Circle() = default;
    Circle(float x_value, float y_value, float radius) : Point(x_value, y_value), r(radius) {}

    float getR() const { return r; }
    void setR(float value) { r = value; }

    float area() const { return shapes::pi * r * r; }  // площадь не храню, а считаю
};

class Pyramid : public Circle {  // пирамида (конус) = круг-основание + высота
private:
    float h = 0.0f;

public:
    Pyramid() = default;
    Pyramid(float x_value, float y_value, float radius, float height)
        : Circle(x_value, y_value, radius), h(height) {}

    float getH() const { return h; }
    void setH(float value) { h = value; }

    float volume() const { return area() * h / 3.0f; }  // объём конуса: S * h / 3
};

class Field {  // поле — прямоугольная площадка, на которой стоят пирамиды
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

    bool contains(float x, float y) const {  // попадает ли точка на поле
        return x >= x_min && x <= x_max && y >= y_min && y <= y_max;
    }

    bool contains(const Circle& circle) const {  // влезает ли основание целиком
        return circle.getX() - circle.getR() >= x_min && circle.getX() + circle.getR() <= x_max &&
               circle.getY() - circle.getR() >= y_min && circle.getY() + circle.getR() <= y_max;
    }
};
