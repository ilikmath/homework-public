// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include "astnode.hpp"

class Add : public ASTNode {  // сложение: левое + правое
  public:
    Add(ASTNode *lhs, ASTNode *rhs);
};

class Sub : public ASTNode {  // вычитание
  public:
    Sub(ASTNode *lhs, ASTNode *rhs);
};

class Mul : public ASTNode {  // умножение
  public:
    Mul(ASTNode *lhs, ASTNode *rhs);
};

class Div : public ASTNode {  // деление
  public:
    Div(ASTNode *lhs, ASTNode *rhs);
};
