#pragma once

#include <iostream>


namespace CrowEngine
{


// #define CORE_LOGIC(COMMENT_OUT_SEGMENT, LOGIC) { \
//     #ifdef COMMENT_OUT_SEGMENT \
//     #elif \
//         LOGIC \
//     #endif
//     };  //there the 'curly braces are important for the data inside LOGIC to be not visible out the LOGIC segment'

//hushhh... these are secrets only a guy like me understands :)
#define CORE_LOGIC(LOGIC) {LOGIC}
#define TEST(CODE) {CODE}

class Logging
{
public:
    template<typename T> static void print(T &&value)
    {
        std::clog << std::forward<T>(value);
    }
};


}