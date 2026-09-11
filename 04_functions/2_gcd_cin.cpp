// 212-Терский-Илья-(Урок 4: упражнения с функциями, аргументами командной строки и рекурсией)

// OTUS C++ basic course examples
// Greatest Common Divisor function implementation

#include <cstdlib>
#include <iostream>
#include <string>

// Greatest Common Divisor (GCD) function
// Uses Euclidean Algorithm - https://en.wikipedia.org/wiki/Euclidean_algorithm
int gcd(int a, int b) {
	while (b != 0) {
		int r = a % b;
		a = b;
		b = r;
	}
	return a;
}

int main(int argc, char* argv[]) {
	if (argc != 3) {
		std::cerr << "Usage: 2_gcd_cin <a> <b>\n";
		return 1;
	}

	try {
		const int a = std::stoi(argv[1]);
		const int b = std::stoi(argv[2]);
		std::cout << "gcd(" << a << ", " << b << ") = " << gcd(a, b) << '\n';
	} catch (const std::exception&) {
		std::cerr << "Both arguments must be integers.\n";
		return 1;
	}

	return 0;
}
