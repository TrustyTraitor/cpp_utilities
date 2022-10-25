#include "permute.hpp"
#include "../Timer/TimerUtils.hpp"

#include <string>
// #include <fstream>

int main() {

	TimerUtils::timer( []() {
		// std::ofstream file;
		std::string str_gen;
		int count = 0;
		
		// file.open("out.txt");

		do {
			count++;
			str_gen = Permute::gen_brute_str(5);

		} while(count < 1000000);
		
		// file << str_gen << std::endl;

		// file.close();
	});

	return 0;
}