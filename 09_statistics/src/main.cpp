// 212-Терский-Илья-Задача(статистические характеристики последовательности)

#include <iostream>
#include <memory>
#include <vector>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#ifndef NOMINMAX
#define NOMINMAX  // иначе windows.h сделает min и max макросами
#endif
#include <windows.h>  // консоль в UTF-8, чтобы ошибки печатались по-русски
#endif

#include "statistics.hpp"

int main() {  // читаю числа до конца ввода (Windows: Ctrl+Z, Enter; Linux: Ctrl+D) и печатаю статистики
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    std::vector<std::unique_ptr<IStatistics>> statistics;  // все статистики через указатель на интерфейс
    statistics.push_back(std::make_unique<Min>());
    statistics.push_back(std::make_unique<Max>());
    statistics.push_back(std::make_unique<Mean>());
    statistics.push_back(std::make_unique<Std>());
    statistics.push_back(std::make_unique<Percentile>(90));
    statistics.push_back(std::make_unique<Percentile>(95));

    double value = 0.0;
    std::size_t count = 0;
    while (std::cin >> value) {
        ++count;
        for (const auto &statistic : statistics) {
            statistic->update(value);
        }
    }

    if (!std::cin.eof()) {  // чтение остановилось не на конце ввода — значит, встретилось не число
        std::cerr << "Ошибка: во входных данных встретилось не число\n";
        return 1;
    }

    if (count == 0) {
        std::cerr << "Ошибка: последовательность пуста\n";
        return 1;
    }

    for (const auto &statistic : statistics) {
        std::cout << statistic->name() << " = " << statistic->eval() << '\n';
    }

    return 0;  // объекты удалит unique_ptr
}
