#pragma once

#include <iostream>
#include <iomanip>
#include <chrono>
#include <functional>
#include <utility>
#include <cmath>

// #include <type_traits>

// template <typename Function, typename... Args>
// decltype(auto) time(Function&& func, Args&&... args)
// {
//     //Floating-point seconds
//     using fpsecond = std::chrono::duration<double, std::ratio<1,1>>;

//     //Keep track of the starting time and declare an ending time
//     std::chrono::steady_clock::time_point startTime = std::chrono::steady_clock::now();
//     double elapsedTime;

//     //If a void function, call it and just return the elapsed time
//     if constexpr (std::is_void_v<std::invoke_result_t<Function, Args...>>)
//     {
//         //Call the passed function with the given arguments (forwarding the arguments to preserve qualifiers)
//         std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);

//         //Record the elapsed time
//         elapsedTime = std::chrono::duration_cast<fpsecond>(std::chrono::steady_clock::now() - startTime).count();

//         //Return the elapsed time (current time - start time) as a double
//         return elapsedTime;
//     }
//     else  //Otherwise, return the return value of the passed function along with the elapsed time as std::pair
//     {
//         decltype(auto) returnValue = std::invoke(std::forward<Function>(func), std::forward<Args>(args)...);

//         //Record the elapsed time
//         elapsedTime = std::chrono::duration_cast<fpsecond>(std::chrono::steady_clock::now() - startTime).count();

//         //Return the called function's return value along with the elapsed time as std::pair
//         return std::make_pair(returnValue, elapsedTime);
//     }
// }

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
