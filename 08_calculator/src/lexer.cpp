#include "lexer.hpp"

#include <cctype>
#include <limits>

#include "syntax_error.hpp"

namespace {

bool is_digit(char ch) { return std::isdigit(static_cast<unsigned char>(ch)) != 0; }  // через unsigned char, иначе русские буквы ломают isdigit
bool is_alpha(char ch) { return std::isalpha(static_cast<unsigned char>(ch)) != 0; }
bool is_space(char ch) { return std::isspace(static_cast<unsigned char>(ch)) != 0; }

}  // namespace

Lexer::Token Lexer::next_token() {  // конечный автомат: состояние + текущий символ решают, что дальше
    for (;;) {
        switch (state_) {
        case State::End:
            return Token::End;
        case State::ReadNumber:
            if (end()) {
                state_ = State::End;
                return Token::Number;
            }
            if (is_digit(ch_)) {
                const int digit = ch_ - '0';
                if (number_ > (std::numeric_limits<int>::max() - digit) / 10) {  // число не влезет в int
                    throw SyntaxError("слишком большое число");
                }
                number_ = 10 * number_ + digit;  // дописываю цифру справа
                next_char();
                break;
            }
            if (is_alpha(ch_)) {
                throw SyntaxError("после числа сразу идёт буква '" + std::string(1, ch_) + "'");
            }
            state_ = State::Empty;
            return Token::Number;
        case State::Empty:
            if (end()) {
                state_ = State::End;
                return Token::End;
            }
            if (is_space(ch_)) {
                next_char();
                break;
            }
            if (isoperator(ch_)) {
                operator_ = ch_;
                next_char();
                return Token::Operator;
            }
            if (ch_ == '(') {
                next_char();
                return Token::Lbrace;
            }
            if (ch_ == ')') {
                next_char();
                return Token::Rbrace;
            }
            if (is_digit(ch_)) {
                number_ = ch_ - '0';
                state_ = State::ReadNumber;
                next_char();
                break;
            }
            if (is_alpha(ch_)) {
                name_ = ch_;
                next_char();
                if (!end() && (is_alpha(ch_) || is_digit(ch_))) {  // «ab» — ошибка по условию
                    throw SyntaxError("имя переменной должно быть одной буквой");
                }
                return Token::Name;
            }
            throw SyntaxError("недопустимый символ '" + std::string(1, ch_) + "'");  // в заготовке тут был вечный цикл
        }
    }
}
