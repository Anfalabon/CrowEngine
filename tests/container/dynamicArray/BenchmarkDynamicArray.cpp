
//#include "gtest/gtest.h"
#include "benchmark/benchmark.h"

#include "DynamicArray.hpp"





static void BM_DynamicArrayMoveConstructor(benchmark::State &state)
{
    for (auto _ : state)
    {
        unsigned long long testSize = 100000;

        DynamicArray array;

        for (unsigned int i=0; i<testSize; ++i)
        {
            array.Insert(i);
        }

        DynamicArray array2 = std::move(array);

        for (unsigned int i=0; i<array2.Size(); ++i)
        {
            //EXPECT_EQ(array2[i], i);
            //std::cout << "Value of array2[" << i << "] is :" << array2[i] << '\n';
        }
    }
}




BENCHMARK(BM_DynamicArrayMoveConstructor);
BENCHMARK_MAIN();
