#pragma once

#include <iostream>
#include <chrono>


namespace CrowEngine
{

//hushhh... these are secrets only a guy like me understands :)

// #define CORE_LOGIC(COMMENT_OUT_SEGMENT, LOGIC) { \
//     #ifdef COMMENT_OUT_SEGMENT \
//     #elif \
//         LOGIC \
//     #endif
//     };  //there the 'curly braces are important for the data inside LOGIC to be not visible out the LOGIC segment'

#define CORE_LOGIC(LOGIC) {LOGIC};
#define TEST(CODE) {CODE};
#define CORE_LOGIC_V2(ABOUT, LOGIC) {LOGIC};
#define TEST_STACK_FRAME(CODE) static void Test(){ CODE }; Test();

class Logging
{
public:
    template<typename T> static void print(T &&value)
    {
        std::clog << std::forward<T>(value);
    }
};


#define Benchmark(CODE) auto start = std::chrono::high_resolution_clock::now(); \
    CODE \
    auto end = std::chrono::high_resolution_clock::now(); \
    auto duration = duration_cast<std::chrono::seconds>(end-start); \
    std::cout << "Execution time: " << duration.count() << " seconds\n";

}