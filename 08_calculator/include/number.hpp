// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include <string>

#include "astnode.hpp"

using namespace std;

class Number : public ASTNode {  // целое число — лист дерева
  public:
    Number(int val)
        : ASTNode(to_string(val))
        , val_(val) {}

    int value() const { return val_; }

  private:
    int val_;
};
