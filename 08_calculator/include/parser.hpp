// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include <istream>
#include <string>

#include "astnode.hpp"
#include "lexer.hpp"

class Parser {  // парсер рекурсивным спуском: из токенов строит дерево
  public:
    explicit Parser(Lexer &lexer)
        : lexer_(lexer) {}

    Parser(const Parser &other) = delete;
    Parser &operator=(const Parser &other) = delete;

    ~Parser() = default;

    ASTNode *parse();  // всё выражение целиком; дерево потом удаляет вызывающий

  private:
    void next_token();

    std::string describe(Lexer::Token token) const;  // токен словами, для текста ошибки

    ASTNode *expr();  // сумма/разность
    ASTNode *term();  // произведение/частное
    ASTNode *prim();  // число, переменная или скобка

    Lexer &lexer_;
    Lexer::Token tok_;
};
