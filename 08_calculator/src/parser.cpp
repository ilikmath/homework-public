#include "parser.hpp"

#include <memory>

#include "number.hpp"
#include "operations.hpp"
#include "syntax_error.hpp"
#include "variable.hpp"

using namespace std;

using Token = Lexer::Token;

ASTNode *Parser::parse() {  // куски дерева держу в unique_ptr: при ошибке они удалятся сами
    unique_ptr<ASTNode> root(expr());
    if (tok_ != Token::End) {  // разобрали выражение, а строка не кончилась
        throw SyntaxError("лишнее в конце выражения: " + describe(tok_));
    }
    return root.release();
}

void Parser::next_token() { tok_ = lexer_.next_token(); }

string Parser::describe(Token token) const {
    switch (token) {
    case Token::Number:
        return "число " + to_string(lexer_.get_number());
    case Token::Operator:
        return "оператор '" + lexer_.get_operator() + "'";
    case Token::Name:
        return "переменная " + lexer_.get_name();
    case Token::Lbrace:
        return "'('";
    case Token::Rbrace:
        return "')'";
    case Token::End:
        return "конец выражения";
    }
    return "неизвестный токен";
}

ASTNode *Parser::expr() {  // E -> T | E + T | E - T, цикл даёт 3 - 4 - 5 = (3 - 4) - 5
    unique_ptr<ASTNode> root(term());
    while (tok_ == Token::Operator) {
        const char op = lexer_.get_operator().front();
        if (op != '+' && op != '-') {
            break;
        }
        unique_ptr<ASTNode> rhs(term());
        if (op == '+') {
            root.reset(new Add(root.release(), rhs.release()));
        } else {
            root.reset(new Sub(root.release(), rhs.release()));
        }
    }
    return root.release();
}

ASTNode *Parser::term() {  // T -> P | T * P | T / P
    unique_ptr<ASTNode> root(prim());
    while (tok_ == Token::Operator) {
        const char op = lexer_.get_operator().front();
        if (op != '*' && op != '/') {
            break;
        }
        unique_ptr<ASTNode> rhs(prim());
        if (op == '*') {
            root.reset(new Mul(root.release(), rhs.release()));
        } else {
            root.reset(new Div(root.release(), rhs.release()));
        }
    }
    return root.release();
}

ASTNode *Parser::prim() {  // P -> Number | Name | ( E )
    unique_ptr<ASTNode> node;
    next_token();
    switch (tok_) {
    case Token::Number:
        node.reset(new Number(lexer_.get_number()));
        break;
    case Token::Name:
        node.reset(new Variable(lexer_.get_name()));
        break;
    case Token::Lbrace:
        node.reset(expr());  // внутри скобок снова целое выражение
        if (tok_ != Token::Rbrace) {
            throw SyntaxError("нет закрывающей скобки, встретилось: " + describe(tok_));
        }
        break;
    default:
        throw SyntaxError("ожидалось число, переменная или '(', а встретилось: " +
                          describe(tok_));
    }
    next_token();
    return node.release();
}
