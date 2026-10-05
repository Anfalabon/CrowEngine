
#include "gtest/gtest.h"

#include "core/Essentials.hpp"

#include <iostream>
#include <memory>
#include <vector>
#include <string.h>
#include <immintrin.h>



class Player
{

public:

    Player() = default;
    ~Player() = default;

    Player(const Player&) = default;
    Player &operator=(const Player &other) = default;

private:

};




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


static void CustomAllocator()
{
    unsigned int size = 1024;
    alignas(int) char storage[size];
    unsigned int *array = new(storage) unsigned int;

    unsigned int numberOfElements = size/sizeof(unsigned int);

    for (unsigned int i = 0; i < numberOfElements; ++i)
    {
        array[i] = i;
    }

    for (unsigned int i = 0; i < size; ++i)
    {
        std::cout << array[i] << '\n';
    }
}




class DynamicArray
{
public:


    DynamicArray() : m_data(nullptr), m_size(0), m_capacity(0), m_allocations(0){}

    ~DynamicArray()
    {
        if (m_data)
        {
            delete[] m_data;
        }
        m_size = 0;
        m_capacity = 0;
    }

    DynamicArray(unsigned int numberOfElements) : m_size(numberOfElements)
    {
        //This kind of initialization(using the m_size) is supported in c++20
        m_data = new int[m_size](m_size);
        memset(m_data, 0, m_size*sizeof(int));
    }


    DynamicArray(const DynamicArray &other)
    {
        if (this == &other)
        {
            return;
        }

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        //Other members will be the default
        //Like 'm_allocation' is unique by DynamicArray instance.
        //But initially the number of allocations would be zero.

        m_data = new int[m_size];
        m_allocations = 1;

        if (m_data)
        {
            memcpy(m_data, other.m_data, m_size*sizeof(int));
        }


    }





    //vec1 = vec2; ---> vec1.operator(vec2)
    DynamicArray &operator=(const DynamicArray &other)
    {
        if (this == &other)
        {
            return *this;
        }

        m_size = other.m_size;
        m_capacity = other.m_capacity;
        //Other members will be the default
        //Like 'm_allocation' is unique by DynamicArray instance.

        m_data = new int[m_size];
        m_allocations = 1;

        if (m_data && other.m_data)
        {
            memcpy(m_data, other.m_data, m_size*sizeof(int));
        }

        return *this;
    }

    DynamicArray(DynamicArray &&) = default;
    DynamicArray &operator=(DynamicArray &&) = default;


    static void *operator new(std::size_t size)
    {
        void *ptr = malloc(size*sizeof(int));
        if (!ptr){std::__throw_bad_alloc();return ptr;} //this shouldn't be bad_alloc
        return ptr;
    }


    [[deprecated("This is still under construction!")]] void PreAllocV1(unsigned int amountToPreAlloc)
    {
        //if m_data isn't empty then we shouldn't PreAlloc() (Atleast for now)
        if (m_data){return;}

        //This function doesn't increase the size of the array.
        //Cause we are just allocating memory and zero-initializing the int bytes.

        m_capacity = amountToPreAlloc;

        if (m_capacity > m_maxStackSize)
        {
            void *heapStorage = malloc(m_capacity*sizeof(int));
            ++m_allocations;
            m_data = new(heapStorage) int(0);
            //m_data = reinterpret_cast<int*>(heapStorage);

            //free(storage);
            return;
        }



        alignas(int) unsigned char stackStorage[m_capacity*sizeof(int)];
        m_data = new(stackStorage) int(0);
        //m_data = reinterpret_cast<int*>(stackStorage);
    }




    void PreAlloc(unsigned int amountToPreAlloc)
    {
        if (m_data)
        {
            //Should we really throw bad_alloc here?
            std::__throw_bad_alloc();
            return;
        }
        m_capacity = amountToPreAlloc;
        m_data = new int[m_capacity];
        ++m_allocations;
    }


    [[deprecated("This was for Testing purpose!")]] void InsertV1(unsigned int value)
    {

        if (!m_data)
        {
            ++m_size;
            m_data = new int[m_size];
            m_data[m_size-1] = value;
            //(m_size-1)[m_data] = value; //lol don't do it
            ++m_allocations;
            return;
        }

        ++m_size;
        int *tempStorage = new int[m_size];
        ++m_allocations;

        memcpy(tempStorage, m_data, (m_size-1)*sizeof(int));

        tempStorage[m_size-1] = value;

        if (!m_data){return;}
        delete[] m_data;

        m_data = tempStorage;
    }


    void Insert(unsigned int value)
    {

        //At first increase the size by 1 as we will already going increase the size anyway.
        //Allocate memory for new array.
        //Copy all the contents of m_data(the previous one) in 'tempStorage'.
        //But remember copy exactly 'm_size-1' elements not 'm_size' because 'memcpy' has to read from the old data which still has 'm_size-1' elements(it checks the end of the old data using the given size)
        //Later assign the last element of 'tempStorage' to the new 'value' from parameter
        //Delete the old content in m_data(as it's already in 'tempStorage')
        //Make the 'm_data' point to the same starting address of tempStorage
        //As 'tempStorage' has automatic storage duration it's going to be destroyed from the current stack frame anyway
        //But the underlying data of 'tempStorage' is not going to be deleted as it's heap allocated.
        //So at the end we have only 'm_data' pointer to the content(single ownership)

        if (m_capacity > m_size) [[likely]]
        {
            ++m_size;
            m_data[m_size-1] = value;
            return;
        }
        else if (m_capacity < m_size)   [[unlikely]]
        {
            std::__throw_out_of_range("Array size greater than capacity!");
            return;
        }

        //Putting it after the first 'if' branch because this is most probably going to be run for the first time or when we delete the contents of the array
        //Otherwise this needs to be checked unnesserily everytime we run this function
        //TODO: For some reason m_data might get deleted and it's underlying m_size and m_capacity might or not get reinitialized
        if (!m_data && m_size == 0 && m_capacity == 0)
        {
            ++m_size;
            //Remeber as long as there is no read/write instruction such as 'array[i]=xyz' the Virtual Memory won't be mapped to Physical Memory.
            //So even if we do '100000*m_size'(for instance) it's still not a deal But...
            //But if the 'm_capacity' is too large then 'new int[m_capacity]' will give error.
            m_capacity = 100*m_size; //Also remeber this is a guess(rough) amount. We need to optimze it too
            m_data = new int[m_capacity];
            m_data[m_size-1] = value;
            ++m_allocations;
            return;
        }



        ++m_size;
        //TODO: Apply an optimization here instead of guessing the 'm_capacity'.
        unsigned int m_preAlloc = 1000; //Remeber this is a guess(rough) amount. We need to optimze it too
        //m_capacity = 20*m_size;
        m_capacity = m_size + m_preAlloc;
        //Utilize 'm_capacity' here instead of calling new each time we need to to insert value
        int *tempStorage = new int[m_capacity];
        //void *tempStorage = new int[m_size];

        //This is right now needed only for logging.
        ++m_allocations;

        //It heavily uses SIMD or Word-aligned copies for efficiency
        //See https://learnmandu.com/blog/memc/blogs/memset-memcpy-memmove-c for more details
        memcpy(tempStorage, m_data, (m_size-1)*sizeof(int));

        tempStorage[m_size-1] = value;

        if (!m_data){return;}
        delete[] m_data;

        m_data = tempStorage;
        //m_data = new(tempStorage) int;


    }

    //Accelerate with SIMD/Word-Aligned copies
    void TestSIMD()
    {
        // #pragma omp simd
        // for (unsigned int i=0; i<m_size-1; ++i)
        // {
        //     tempStorage[i] = m_data[i];
        // }

        ////TODO: Add SIMD or Word-Aligned copies manually from intrinsics
        ////See https://gist.github.com/MangaD/1fad63756ad8c946ce01dd1d52eff173 for details
        // for (unsigned int i=0; i<m_size; i+=sizeof(int))
        // {
        //     __m256 bufferVecA = _mm256_loadu_ps();
        //     __m256 bufferVecB = _mm256_loadu_ps();
        // }
    }


    void RemoveLast()
    {
        //Deletion of the last element should also follow the 'm_capacity' optimization
        if (m_capacity > m_size && m_size != 0 /*Two trivial cases*/)
        {
            //We need to apply security here
            //Cause if the old data is still there then it could cause security issues

            //If we do this then the memory is not deleted and it still remain's there with the value '0'.
            //But the issue is we might have a lot's of unnecessary memory wastage.
            m_data[m_size-1] = 0;
            --m_size;
            return;
        }


        if (m_capacity > m_maxCapacity)
        {
            //Use realloc
        }

        std::__throw_out_of_range("Attempt to delete the last element of an empty array!");
        return;
    }


    inline int &GetValue(unsigned int index) const
    {
        if (index >= m_size){std::__throw_range_error("OUT OF BOUND ACCESS!");}
        return m_data[index];
    }


    inline int &operator[](unsigned int index) const
    {
        if (index >= m_size){std::__throw_range_error("OUT OF BOUND ACCESS!");}
        return m_data[index];
    }


    [[nodiscard]] inline unsigned int Size(){return m_size;}
    [[nodiscard]] inline unsigned int Capacity(){return m_capacity;}
    [[nodiscard]] inline unsigned int Allocations(){return m_allocations;}
    [[nodiscard]] inline unsigned int SizeBytes(){return m_size*sizeof(int);}
    [[nodiscard]] inline unsigned int CapacityBytes(){return m_capacity*sizeof(int);}
    [[nodiscard]] inline bool IsEmpty(){return (m_size == 0);}

    [[nodiscard]] inline int *Data()
    {
        if (!m_data){std::__throw_bad_exception();}
        return m_data;
    }

    void Erase()
    {
        //this->~DynamicArray();
        if (m_data)
        {
            delete[] m_data;
        }
        m_data = nullptr;
        m_size = 0;
        m_capacity = 0;
        m_allocations = 0;
    }


private:

    int *m_data;
    unsigned int m_size;        //m_size is the number of elements currently in the array.
    unsigned int m_capacity;    //m_capacity is the real allocated size for the array.
    unsigned int m_allocations;



private:

    //I still don't know if we need this
    bool m_preAllocated;
    [[deprecated("don't dare to use it boy!")]] bool m_isCapacityGreater;

    //Right now just use an typical amount.
    //Change it later using by getting the system's max stack segment size(int unix it's 8MB(usually) in Windows it's 1MB(usually))
    static constexpr unsigned long m_maxStackSize = 1 * 1024 * 1024; //1MB == 1 * 1024 KB == 1 * 1024 * 1024 B;
    static constexpr unsigned long m_maxCapacity  = 1 * 1024 * 1024 * 1024; //1GB



};





namespace Container
{


typedef struct Node
{
    int m_data;
    Node *m_next;
}Node;


class LinkedList
{

public:

    //LinkedList() = default;
    ~LinkedList() = default;

    LinkedList()
    {
        m_current->m_data = 0;
        m_current = nullptr;
    }


    void Insert(int value)
    {
        m_current->m_data = value;
        m_current = m_current->m_next;
    }

    //decltype(m_current->m_data)
    int Last()
    {
        if (m_current)
        {
            //std::throw("");
            return 0;
        }
        return m_current->m_data;
    }

private:

    Node *m_current;


};




}





TEST(DynamicArray_InsertionTest, TestValuesAfterInsertion)
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
