// 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

#include "version.h"

#include <iostream>

int main(int, char**) {

    std::cout << "Hello from the second CMake example!"
        << std::endl;
    std::cout << "Version = " << examples::getVersion()
        << std::endl;

    return 0;
}