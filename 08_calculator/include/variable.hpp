// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include <string>

#include "astnode.hpp"

using namespace std;

class Variable : public ASTNode {  // переменная (одна буква) — лист дерева
  public:
    explicit Variable(const string &name);

    string name() const { return repr(); }
};
