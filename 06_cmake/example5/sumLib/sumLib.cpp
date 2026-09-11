// 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

#include "sumLib.h"
#include "config.h"

#include <iostream>

namespace sumLib {

    int sum(int a, int b) {
        std::cout << "Hello from sumLib!" << std::endl;
        return a + b;
    }

    int getVersion() {
        return (PROJECT_VERSION);
    }

}