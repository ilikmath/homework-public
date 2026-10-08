// 212-Терский-Илья-Задача(пирамиды на 2D-плоскости): квадраты и алгоритм «Волна»

#pragma once

#include <cstdint>
#include <vector>

struct SecondaryPoint {  // вторичная точка — сгенерирована по Гауссу под пирамидой
    float x = 0.0f;
    float y = 0.0f;
    int source = 0;  // под какой пирамидой появилась (номер с 1)
};

class SquareGrid {  // плоскость, порезанная на квадраты («карта Москвы»)
private:
    float x_min = 0.0f;
    float y_min = 0.0f;
    float square_side = 1.0f;
    int column_count = 1;
    int row_count = 1;
    std::vector<int> start;   // где в sorted начинается каждый квадрат (квадратов + 1 штука)
    std::vector<int> sorted;  // номера точек, сложенные по квадратам

public:
    SquareGrid(const std::vector<SecondaryPoint>& points, float side, float x_low, float y_low,
               float x_high, float y_high);

    int columns() const { return column_count; }
    int rows() const { return row_count; }
    float side() const { return square_side; }

    int columnOf(float x) const;  // в каком столбце лежит x
    int rowOf(float y) const;     // в какой строке лежит y
    int cell(int column, int row) const { return row * column_count + column; }  // номер квадрата

    float cornerX(int column) const { return x_min + static_cast<float>(column) * square_side; }  // левый нижний угол
    float cornerY(int row) const { return y_min + static_cast<float>(row) * square_side; }

    int first(int cell_index) const { return start[static_cast<size_t>(cell_index)]; }  // точки квадрата: order()[first..last)
    int last(int cell_index) const { return start[static_cast<size_t>(cell_index) + 1]; }
    const std::vector<int>& order() const { return sorted; }
};

class BitMatrix {  // матрица N×N из нулей и единиц, по 64 штуки в одном слове
private:
    int n = 0;
    int word_count = 0;
    std::vector<std::uint64_t> bits;

public:
    explicit BitMatrix(int size);

    int size() const { return n; }
    int words() const { return word_count; }

    void set(int i, int j);
    bool get(int i, int j) const;
    const std::uint64_t* row(int i) const;
};

BitMatrix buildAdjacency(const std::vector<SecondaryPoint>& points, const SquareGrid& grid,
                         float threshold);  // b_ij = 1, если точки ближе threshold; сторона квадрата должна быть >= threshold

struct WaveResult {
    std::vector<int> cluster;  // номер кластера каждой точки (с 1)
    std::vector<int> wave;     // на каком шаге загорелась точка, точка поджога — 1
    int clusters = 0;
};

WaveResult runWave(const BitMatrix& adjacency);  // «Волна»: поджигаю точку, потом её соседей и так пока горит
