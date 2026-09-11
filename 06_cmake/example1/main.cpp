// 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

// Find all generators
// cmake --help
// Use the default generator
// cmake ..
// Use some other generator
// cmake .. -G "Visual Studio 17 2022"

#include <iostream>

int main(int, char**) {

    std::cout << "Hello from the first CMake example!" << std::endl;

    return 0;
}