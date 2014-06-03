#ifndef OUTPUT_HPP
#define OUTPUT_HPP

#include <iostream>

template <typename T>
void print(const T& value) {
	std::cout << value;
}

template <typename U, typename... T>
void print(const U& head, const T&... tail) {
	std::cout << head;
	print(tail...);
}

template <typename T>
void println(const T& value) {
	std::cout << value << std::endl;
}

template <typename U, typename... T>
void println(const U& head, const T&... tail) {
	std::cout << head;
	println(tail...);
}

template <typename T>
void error(const T& value) {
	std::cerr << value << std::endl;

	std::exit(1);
}

template <typename U, typename... T>
void error(const U& head, const T&... tail) {
	std::cerr << head;
	error(tail...);
}

#endif