// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include <stdexcept>
#include <string>

class SyntaxError : public std::runtime_error {  // ошибка в выражении, ловлю её в main
  public:
    explicit SyntaxError(const std::string &message)
        : std::runtime_error(message) {}
};
