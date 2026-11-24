#pragma once

#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/string_cast.hpp>

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

#define LOG_MATRIX(matrixName, matrix) std::clog << matrixName << ": " << glm::to_string(matrix) << '\n';


static unsigned int function()
{
    return 100;
}

extern unsigned int GetUnsignedInt();
extern const char *GetStr();
extern void *GetMalloc();

// unsigned int GetUnsignedInt();
// const char *GetStr();
// void *GetMalloc();


#define Benchmark(CODE) auto start = std::chrono::high_resolution_clock::now(); \
    CODE \
    auto end = std::chrono::high_resolution_clock::now(); \
    auto duration = duration_cast<std::chrono::seconds>(end-start); \
    std::cout << "Execution time: " << duration.count() << " seconds\n";

}
