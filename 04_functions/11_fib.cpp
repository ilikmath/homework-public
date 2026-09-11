// 212-Терский-Илья-(Урок 4: упражнения с функциями, аргументами командной строки и рекурсией)

// OTUS C++ basic course
// Iterative Fibonacci numbers

#include <cstdlib>
#include <iostream>

// Eval nth fibanicci number
unsigned long fib(unsigned long n) {
	unsigned long previous = 0;
	unsigned long current = 1;

	for (unsigned long index = 0; index < n; ++index) {
		const unsigned long next = previous + current;
		previous = current;
		current = next;
	}

	return previous;
}

int main(int argc, char *argv[]) {
	unsigned long n = 100;
	if (argc == 2) {
		long tmp = std::atol(argv[1]);
		if (tmp < 0) {
			std::cerr << "Only non-negative number allowed\n";
			return 1;
		}
		n = tmp;
	}
	for (unsigned long i = 0; i < n; ++i) {
		std::cout << fib(i) << "\n";
	}
	return 0;
}
