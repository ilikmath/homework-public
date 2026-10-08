#include "operations.hpp"

Add::Add(ASTNode *lhs, ASTNode *rhs)
    : ASTNode("+", lhs, rhs) {}

Sub::Sub(ASTNode *lhs, ASTNode *rhs)
    : ASTNode("-", lhs, rhs) {}

Mul::Mul(ASTNode *lhs, ASTNode *rhs)
    : ASTNode("*", lhs, rhs) {}

Div::Div(ASTNode *lhs, ASTNode *rhs)
    : ASTNode("/", lhs, rhs) {}
