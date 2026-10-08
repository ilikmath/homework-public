// 212-Терский-Илья-Задача(пирамиды на 2D-плоскости): квадраты и алгоритм «Волна»

#include "clusters.h"

#include <algorithm>  // fill, max, min
#include <cmath>      // ceil, floor

namespace {

const int word_bits = 64;

using Row = std::vector<std::uint64_t>;

void setBit(Row& row, int index) {  // поставить единичку в бит index
    row[static_cast<size_t>(index / word_bits)] |= std::uint64_t{1} << (index % word_bits);
}

int lowestBit(std::uint64_t word) {  // номер самого младшего единичного бита (слово не ноль)
    int index = 0;
    while ((word & 1u) == 0u) {
        word >>= 1;
        ++index;
    }
    return index;
}

template <typename Action>
void forEachBit(const Row& row, Action action) {  // вызвать action(i) для всех единичных битов
    for (size_t w = 0; w < row.size(); ++w) {
        std::uint64_t word = row[w];
        while (word != 0u) {
            action(static_cast<int>(w) * word_bits + lowestBit(word));
            word &= word - 1;  // убираю младшую единичку
        }
    }
}

}  // namespace

SquareGrid::SquareGrid(const std::vector<SecondaryPoint>& points, float side, float x_low,
                       float y_low, float x_high, float y_high)  // раскладываю точки по квадратам сортировкой подсчётом
    : x_min(x_low), y_min(y_low), square_side(side) {
    column_count = std::max(1, static_cast<int>(std::ceil((x_high - x_low) / side)));
    row_count = std::max(1, static_cast<int>(std::ceil((y_high - y_low) / side)));

    const size_t cells = static_cast<size_t>(column_count) * static_cast<size_t>(row_count);
    start.assign(cells + 1, 0);
    for (const SecondaryPoint& point : points) {  // сначала считаю, сколько точек в каждом квадрате
        ++start[static_cast<size_t>(cell(columnOf(point.x), rowOf(point.y))) + 1];
    }
    for (size_t c = 0; c < cells; ++c) {  // потом получаю, где начинается каждый квадрат
        start[c + 1] += start[c];
    }

    std::vector<int> next(start.begin(), start.end() - 1);
    sorted.assign(points.size(), 0);
    for (size_t i = 0; i < points.size(); ++i) {  // и раскладываю номера точек по местам
        const size_t c = static_cast<size_t>(cell(columnOf(points[i].x), rowOf(points[i].y)));
        sorted[static_cast<size_t>(next[c]++)] = static_cast<int>(i);
    }
}

int SquareGrid::columnOf(float x) const {  // если точка за краем, прижимаю к крайнему столбцу
    const int column = static_cast<int>(std::floor((x - x_min) / square_side));
    return std::min(std::max(column, 0), column_count - 1);
}

int SquareGrid::rowOf(float y) const {
    const int row = static_cast<int>(std::floor((y - y_min) / square_side));
    return std::min(std::max(row, 0), row_count - 1);
}

BitMatrix::BitMatrix(int size)
    : n(size),
      word_count((size + word_bits - 1) / word_bits),
      bits(static_cast<size_t>(size) * static_cast<size_t>(word_count), 0u) {}

void BitMatrix::set(int i, int j) {
    bits[static_cast<size_t>(i) * static_cast<size_t>(word_count) + static_cast<size_t>(j / word_bits)] |=
        std::uint64_t{1} << (j % word_bits);
}

bool BitMatrix::get(int i, int j) const {
    const std::uint64_t word =
        bits[static_cast<size_t>(i) * static_cast<size_t>(word_count) + static_cast<size_t>(j / word_bits)];
    return ((word >> (j % word_bits)) & 1u) != 0u;
}

const std::uint64_t* BitMatrix::row(int i) const {  // строка i — это сразу все соседи точки i
    return bits.data() + static_cast<size_t>(i) * static_cast<size_t>(word_count);
}

BitMatrix buildAdjacency(const std::vector<SecondaryPoint>& points, const SquareGrid& grid,
                         float threshold) {  // соседей ищу только в своём квадрате и 8 вокруг, а не по всем точкам
    const int n = static_cast<int>(points.size());
    const float limit = threshold * threshold;  // сравниваю квадраты расстояний, чтобы не брать корень
    const std::vector<int>& order = grid.order();
    BitMatrix adjacency(n);

    for (int i = 0; i < n; ++i) {
        const SecondaryPoint& p = points[static_cast<size_t>(i)];
        const int column = grid.columnOf(p.x);
        const int row = grid.rowOf(p.y);

        for (int c = std::max(column - 1, 0); c <= std::min(column + 1, grid.columns() - 1); ++c) {
            for (int r = std::max(row - 1, 0); r <= std::min(row + 1, grid.rows() - 1); ++r) {
                const int square = grid.cell(c, r);
                for (int k = grid.first(square); k < grid.last(square); ++k) {
                    const int j = order[static_cast<size_t>(k)];
                    const SecondaryPoint& q = points[static_cast<size_t>(j)];
                    const float dx = p.x - q.x;
                    const float dy = p.y - q.y;
                    if (j != i && dx * dx + dy * dy <= limit) {
                        adjacency.set(i, j);
                    }
                }
            }
        }
    }

    return adjacency;
}

WaveResult runWave(const BitMatrix& adjacency) {  // фронт, следующий фронт и сгоревшие точки храню битами
    const int n = adjacency.size();
    const size_t words = static_cast<size_t>(adjacency.words());

    WaveResult result;
    result.cluster.assign(static_cast<size_t>(n), 0);
    result.wave.assign(static_cast<size_t>(n), 0);

    Row burnt(words, 0u);
    Row front(words, 0u);
    Row next(words, 0u);

    for (int s = 0; s < n; ++s) {
        if (result.cluster[static_cast<size_t>(s)] != 0) {
            continue;  // точка уже в каком-то кластере
        }

        const int id = ++result.clusters;  // поджигаю новую точку — начинается новый кластер
        std::fill(front.begin(), front.end(), 0u);
        setBit(front, s);
        setBit(burnt, s);
        result.cluster[static_cast<size_t>(s)] = id;
        result.wave[static_cast<size_t>(s)] = 1;

        for (int step = 2;; ++step) {
            std::fill(next.begin(), next.end(), 0u);
            forEachBit(front, [&](int i) {  // следующий фронт = «или» строк всех точек фронта
                const std::uint64_t* neighbours = adjacency.row(i);
                for (size_t w = 0; w < words; ++w) {
                    next[w] |= neighbours[w];
                }
            });

            bool changed = false;
            for (size_t w = 0; w < words; ++w) {  // выкидываю уже сгоревшие точки
                next[w] &= ~burnt[w];
                burnt[w] |= next[w];
                changed = changed || next[w] != 0u;
            }
            if (!changed) {
                break;  // ничего нового не загорелось — волна погасла
            }

            forEachBit(next, [&](int i) {
                result.cluster[static_cast<size_t>(i)] = id;
                result.wave[static_cast<size_t>(i)] = step;
            });
            std::swap(front, next);
        }
    }

    return result;
}
