// 212-Терский-Илья-(Задание 2: запуск Hello World и функций из отдельных модулей)

#include "example.h"
#include "move_me_out.h"

#include <iostream>

int main() {
    std::cout << "Hello, World!" << std::endl;

    example_function();
    todo_move_me_out();

    return 0;
}
