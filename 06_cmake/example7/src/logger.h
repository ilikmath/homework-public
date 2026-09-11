// 212-Терский-Илья-(Урок 6: конфигурация и сборка программ с CMake)

#pragma once

#include <string>

namespace logger {

    void info(const std::string& msg);

    void warning(const std::string& msg);

    void error(const std::string& msg);

    void fatal(const std::string& msg);

}