// 212-Терский-Илья-(Урок 5: модульность, единицы трансляции и библиотеки)

#include "calculation.h"

#include <iostream>

int make_some_calculcation(int arg1, int arg2) {
	std::cout << "Hello from super calculator V1!" << std::endl;
	return arg1 + arg2;
}