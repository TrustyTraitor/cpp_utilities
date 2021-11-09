#ifndef TIMER_UTILS_MG
#define TIMER_UTILS_MG

#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <utility>
#include <cmath>


namespace TimerUtils {

    /*
        To use this timer call create an instance of this struct when your function first begins
        When the function goes out of scope it will automatically call the destructor which will
        calculate and display the time the function took to run
    */
    struct Timer {

        std::chrono::high_resolution_clock::time_point start, end;
        std::chrono::duration<double, std::nano> duration;

        Timer() {
            start = std::chrono::high_resolution_clock::now();
        }

        ~Timer() {
            std::cout << std::fixed;
            end = std::chrono::high_resolution_clock::now();
            duration = std::chrono::duration_cast<std::chrono::nanoseconds>(end-start);

            std::cout << "Took " << duration.count()/std::pow(10,6) << " milliseconds." << std::endl;
        }
    };

	template<typename Function, typename... Args>
	void timer(Function&& func, Args&&... args) {
		Timer ttt;

		std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);
	}

}

#endif