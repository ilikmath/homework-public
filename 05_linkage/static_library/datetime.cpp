// 212-Терский-Илья-(Урок 5: модульность, единицы трансляции и библиотеки)

#include "datetime.h"

#include <iostream>
#include <iomanip>
#include <ctime>
#include <sstream>

std::string getCurrentDateTime() {
	std::time_t t = std::time(nullptr);
	std::tm local = *std::localtime(&t);

	std::ostringstream oss;
	oss << std::put_time(&local, "%d-%m-%Y %H-%M-%S");
	return oss.str();
}