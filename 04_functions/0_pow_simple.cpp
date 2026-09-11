// 212-Терский-Илья-(Урок 4: упражнения с функциями, аргументами командной строки и рекурсией)

#include <iomanip>
#include <iostream>

int main() {

	double base = 0;
	int exponent = 0;

	std::cout << "Enter base: ";
	if (!(std::cin >> base)) {
		std::cerr << "Base must be a number.\n";
		return 1;
	}

	std::cout << "Enter exp: ";
	if (!(std::cin >> exponent) || exponent < 0) {
		std::cerr << "Exponent must be a non-negative integer.\n";
		return 1;
	}

	double result = 1;
	for (int i = 0; i < exponent; ++i) {
		result *= base;
	}

	std::cout << std::setprecision(10) << "pow(" << base << ", " << exponent << ") = " << result << '\n';
	// pow(3.1415926, 8) = 9488.529721

	return 0;
}
