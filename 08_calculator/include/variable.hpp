// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include <string>

#include "astnode.hpp"

class Variable : public ASTNode {  // переменная (одна буква) — лист дерева
  public:
    explicit Variable(const std::string &name);

    std::string name() const { return repr(); }
};
