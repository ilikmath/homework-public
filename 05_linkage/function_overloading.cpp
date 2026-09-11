// 212-Терский-Илья-(Урок 5: модульность, единицы трансляции и библиотеки)

#include <iostream>
#include <string>
#include <vector>

// ("",  '.') -> [""]
// ("11", '.') -> ["11"]
// ("..", '.') -> ["", "", ""]
// ("11.", '.') -> ["11", ""]
// (".11", '.') -> ["", "11"]
// ("11.22", '.') -> ["11", "22"]
std::vector<std::string> split(const std::string &str, char delimiter) {
	std::vector<std::string> r;

	std::string::size_type start = 0;
	std::string::size_type stop = str.find_first_of(delimiter);
	while(stop != std::string::npos) {
		r.push_back(str.substr(start, stop - start));

		start = stop + 1;
		stop = str.find_first_of(delimiter, start);
	}

	r.push_back(str.substr(start));

	return r;
}

std::vector<std::string> split(const char * str, char delimiter) {
	return split(
		std::string{str}, delimiter
	);
}

void split_example() {
	std::cout << "\nsplit_example" << std::endl;

	std::string str = "Hello, World! Nice to meet you!";
	std::vector<std::string> tokens = split(str, ' ');

	std::cout << "str tokens:" << std::endl;
	for(const auto& t : tokens) {
		std::cout << t << std::endl;
	}
	std::cout << std::endl;

	const char * c_str = "Hello, World! Nice to meet you!";
	std::vector<std::string> tokens2 = split(c_str, ' ');

	split(c_str, ' ');

	std::cout << "c_str tokens:" << std::endl;
	for(const auto& t : tokens2) {
		std::cout << t << std::endl;
	}
	std::cout << std::endl;

	std::cout << std::endl;
}







void func() {
	std::cout << "func without args" << std::endl;
}

void func(int arg) {
	std::cout << "func with one int arg" << std::endl;
}

void func(float arg) {
	std::cout << "func with one float arg" << std::endl;
}

void func(int arg1, float arg2) {
	std::cout << "func with one int and one float args" << std::endl;
}

// Ooops!
// void func(float arg1, float arg2, const char * arg3 = nullptr) {
// 	std::cout << "func with one int arg,"
// 		" one float arg "
// 		" and one const char * arg with default value" << std::endl;
// }

void func_example() {
	func();
	func(42);
	func(42, 3.14f);
}


int main() {
	split_example();

	func_example();

	return 0;
}