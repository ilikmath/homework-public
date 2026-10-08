// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include <cctype>
#include <iostream>
#include <string>

class ASTNode {  // узел дерева разбора: подпись + левое и правое поддерево
  public:
    explicit ASTNode(const std::string &repr);  // лист, без детей

    ASTNode(const std::string &repr, ASTNode *lhs, ASTNode *rhs);  // узел с детьми, забирает их себе

    ASTNode(const ASTNode &other) = delete;             // копировать нельзя: иначе два узла удалят одних детей
    ASTNode &operator=(const ASTNode &other) = delete;  // правило трёх

    virtual ~ASTNode();  // виртуальный, потому что удаляю наследников через ASTNode*

    std::string repr() const { return repr_; }

    void print(std::ostream &out) const;  // печать дерева, уложенного набок

  private:
    void inner_print(std::ostream &out, size_t indent) const;

    std::string repr_;
    ASTNode *lhs_;
    ASTNode *rhs_;
};
