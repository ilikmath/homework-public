// 212-Терский-Илья-Задача(инженерный калькулятор)

#pragma once

#include <stdexcept>
#include <string>

using namespace std;

class SyntaxError : public runtime_error {  // ошибка в выражении, ловлю её в main
  public:
    explicit SyntaxError(const string &message)
        : runtime_error(message) {}
};
