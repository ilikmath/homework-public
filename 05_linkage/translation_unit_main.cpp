// 212-Терский-Илья-(Урок 5: модульность, единицы трансляции и библиотеки)

#include "translation_unit1.h"
#include "translation_unit2.h"

#include <iostream>

int main() {

	float value = my_super_sum(1.0f, 2.0f);
	std::cout << "value = " << value << std::endl;

	int value2 = my_super_mul(12, 32);
	std::cout << "value2 = " << value2 << std::endl;

	return 0;
}