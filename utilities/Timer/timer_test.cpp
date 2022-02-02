#include "TimerUtils.hpp"
#include <iostream>

template<typename T>
int add(T first) { // This works
	return first;
}

template<typename T, typename... Args>
int add(T first, Args... args) { // this works
	return first + add(args...);
}

template<typename T>
void print(T input){ 
	std::cout << input << std::endl;
}

void test() {
	printf("thing");
}

int main() {

	TimerUtils::timer(print<std::string>, "output");
	TimerUtils::timer(test);
	std::cout << add(1,2,3);

}