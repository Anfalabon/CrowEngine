
#include "gtest/gtest.h"
#include "benchmark/benchmark.h"

#include "core/Essentials.hpp"
#include "DynamicArray.hpp"




template<typename T>
static void RecievePtr_CRef(const std::unique_ptr<T> &ptr)
{
    std::cout << ptr.get() << '\n';
}


template<typename T>
static void RecievePtr_RRef(std::unique_ptr<T> &ptr)
{
    std::cout << ptr.get() << '\n';
}


static void TestUniquePtr()
{
    // std::unique_ptr<int> ptr = std::make_unique<int>(10);
    //
    // RecievePtr_CRef(ptr);
    // RecievePtr_RRef(ptr);
}












TEST(DynamicArray_InsertionTest, DISABLED_TestValuesAfterInsertion)
{
    unsigned long long testSize = 10;

    DynamicArray array;

    for (unsigned int i=0; i<testSize; ++i)
    {
        array.Insert(i);
    }

    for (unsigned int i=0; i<array.Size(); ++i)
    {
        EXPECT_EQ(array[i], i);
        std::cout << "Value of array[" << i << "] is :" << array[i] << '\n';
    }

    RecordProperty("SizeOfTheArray", array.Size());

}



TEST(DynamicArray_EqualityTests, DISABLED_TestValuesAfterAssignment)
{
    unsigned long long testSize = 10;

    DynamicArray array;

    for (unsigned int i=0; i<testSize; ++i)
    {
        array.Insert(i);
    }


    DynamicArray array2;
    array2 = array;

    for (unsigned int i=0; i<array2.Size(); ++i)
    {
        EXPECT_EQ(array[i], array2[i]);
    }

}





TEST(TestDynamicArrayMoveSemantics, TestMoveConstructor)
{
    unsigned long long testSize = 10000;

    DynamicArray array;

    for (unsigned int i=0; i<testSize; ++i)
    {
        array.Insert(i);
    }

    DynamicArray array2 = std::move(array);

    for (unsigned int i=0; i<array2.Size(); ++i)
    {
        EXPECT_EQ(array2[i], i);
        //std::cout << "Value of array2[" << i << "] is :" << array2[i] << '\n';
    }

}






int main()
{



    // const char *a = "Hello, World!";
    // const int *b = nullptr;


    // while (!false/*fun*/)
    // {
    //         std::cout << "Enter the size to be tested: ";
    //         std::cin >> testSize;
    //         std::cin.get();
    //
    //     Benchmark(
    //
    //         array.PreAlloc(testSize);
    //         array.Insert(10);
    //
    //
    //         // for (unsigned int i=0; i<testSize; ++i)
    //         // {
    //         //     array.Insert(i);
    //         //     //std::cout << array[i] << '\n';
    //         // }
    //
    //         // for (unsigned int i=0; i<testSize; ++i)
    //         // {
    //         //     std::cout << array[i] << '\n';
    //         // }
    //
    //         // for (unsigned int i=1; i<=testSize/2; ++i)
    //         // {
    //         //     array.RemoveLast();
    //         // }
    //
    //         // for (unsigned int i=0; i<testSize/2; ++i)
    //         // {
    //         //     std::cout << array[i] << '\n';
    //         // }
    //
    //
    //         std::cout << "The size of the array is: " << array.Size() << '\n';;;"no issue lol";
    //         std::cout << "The capacity of the array is: " << array.Capacity() << '\n';
    //         std::cout << "The size of the array in bytes is: " << array.SizeBytes() << " Bytes" << '\n';
    //         std::cout << "The capacity of the array in bytes is: " << array.CapacityBytes() << " Bytes" << '\n';
    //         std::cout << "The number of allocation done is: " << array.Allocations() << '\n';
    //
    //
    //         std::cin.get();
    //         array.Erase();
    //
    //
    //         //keep it away
    //     )
    // }


"no issue lol";
;;;;    //giving semicolons here is not a problem



    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}





#if defined(VERSION_1)
static void sleepForWhile(std::size_t N)
{
    std::cout << "Waiting..." << '\n';
    std::this_thread::sleep_for (std::chrono::seconds(N));
}



int main()
{

    {
        std::size_t data =
        #include "data.inc"
            ;

        std::cout << data << '\n';
    }



    int sum = 0;
    volatile bool isRunning = true;
    while (isRunning)
    {
        sum += 10;
        if (sum == 100)
            break;
    }


    std::cout << sum << '\n';


    return 0;

}
#endif
