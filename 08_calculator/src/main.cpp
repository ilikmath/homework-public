// 212-Терский-Илья-Задача(инженерный калькулятор: дерево разбора арифметического выражения)

#include <iostream>
#include <memory>

#ifdef _WIN32
#define WIN32_LEAN_AND_MEAN
#include <windows.h>  // консоль в UTF-8, чтобы ошибки печатались по-русски
#endif

#include "astnode.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include "syntax_error.hpp"

int main() {  // читаю одно выражение и печатаю его дерево набок
#ifdef _WIN32
    SetConsoleOutputCP(CP_UTF8);
#endif

    try {
        Lexer lexer(std::cin);
        Parser parser(lexer);

        const std::unique_ptr<ASTNode> ast(parser.parse());  // unique_ptr сам удалит дерево в конце
        ast->print(std::cout);
    } catch (const SyntaxError &error) {
        std::cerr << "Ошибка: " << error.what() << '\n';
        return 1;
    }

    return 0;
}
