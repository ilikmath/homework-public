#include "astnode.hpp"

using namespace std;

ASTNode::ASTNode(const string &repr)
    : repr_(repr)
    , lhs_{nullptr}
    , rhs_{nullptr} {}

ASTNode::ASTNode(const string &repr, ASTNode *lhs, ASTNode *rhs)
    : repr_(repr)
    , lhs_{lhs}
    , rhs_{rhs} {}

ASTNode::~ASTNode() {  // удаляю детей, а они своих — так освобождается всё дерево
    delete lhs_;
    delete rhs_;
}

void ASTNode::print(ostream &out) const { inner_print(out, 0); }

void ASTNode::inner_print(ostream &out, size_t indent) const {  // левое поддерево, сам узел, правое; отступ = глубина
    if (lhs_) {
        lhs_->inner_print(out, indent + 1);
    }
    for (size_t i = 0; i < indent; ++i) {
        out << "    ";
    }
    out << repr_ << '\n';
    if (rhs_) {
        rhs_->inner_print(out, indent + 1);
    }
}
