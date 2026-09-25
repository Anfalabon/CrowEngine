

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
        delete[] m_data;
        m_size = 0;
        m_capacity = 0;
    }

    DynamicArray(unsigned int numberOfElements) : m_size(numberOfElements)
    {
        //we can use malloc() here too
        //m_data = new int[m_size](numberOfElements);
        //for (unsigned int i=0; i<m_size; ++i){m_data[i] = 0;}
    }


    void PreAlloc(unsigned int amountToPreAlloc)
    {
        //if m_data isn't empty then we shouldn't PreAlloc() (Atleast for now)
        if (m_data && m_size == 0 && m_capacity == 0){return;}

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

        //bad
        // m_isCapacityGreater = m_capacity < m_size;
        //
        // switch ((int)m_isCapacityGreater)
        // {
        //     case 0:
        //         ++m_size;
        //         m_data[m_size-1] = value;
        //         return;
        //     break;
        //     case 1:
        //         std::__throw_out_of_range("Number of elements greater than Capacity!");
        //         return;
        //     break;
        // }


        if (m_capacity > m_size)
        {
            ++m_size;
            m_data[m_size-1] = value;
            return;
        }
        else if (m_capacity < m_size)   [[unlikely]]
        {
            std::__throw_out_of_range("Number of elements greater than Capacity!");
            return;
        }

        //Putting it after the first 'if' branch because this is most probably going to be run for the first time or when we delete the contents of the array
        //Otherwise this needs to be checked unnesserily everytime we run this function
        //TODO: For some reason m_data might get deleted and it's underlying m_size and m_capacity might or not get reinitialized
        if (!m_data && m_size == 0 && m_capacity == 0)
        {
            ++m_size;
            m_capacity = 100*m_size; //Remeber this is a guess(rough) amount. We need to optimze it too
            m_data = new int[m_capacity];
            m_data[m_size-1] = value;
            ++m_allocations;
            return;
        }



        ++m_size;
        //TODO: Apply an optimization here instead of guessing the 'm_capacity'.
        m_capacity = 20*m_size;  //Remeber this is a guess(rough) amount. We need to optimze it too
        //Utilize 'm_capacity' here instead of calling new each time we need to to insert value
        int *tempStorage = new int[m_capacity];
        //void *tempStorage = new int[m_size];

        //This is right now needed only for logging.
        ++m_allocations;

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


        //It heavily uses SIMD or Word-aligned copies for efficiency
        //See https://learnmandu.com/blog/memc/blogs/memset-memcpy-memmove-c for more details
        memcpy(tempStorage, m_data, (m_size-1)*sizeof(int));

        tempStorage[m_size-1] = value;

        delete[] m_data;

        m_data = tempStorage;
        //m_data = new(tempStorage) int;


    }


    void RemoveLast()
    {
        //Deletion of the last element should also follow the 'm_capacity' optimization
    }


    const inline int &GetValue(unsigned int index) const
    {
        if (index >= m_size){std::__throw_range_error("OUT OF BOUND ACCESS!");}
        return m_data[index];
    }


    const inline int &operator[](unsigned int index) const
    {
        if (index >= m_size){std::__throw_range_error("OUT OF BOUND ACCESS!");}
        return m_data[index];
    }


    inline unsigned int Size(){return m_size;}
    inline unsigned int Allocations(){return m_allocations;}

    inline int *Data()
    {
        if (!m_data){std::__throw_bad_exception();}
        return m_data;
    }

    inline void Erase()
    {
        //this->~DynamicArray();
        delete[] m_data;
        m_size = 0;
        m_capacity = 0;
    }




private:

    int *m_data;
    unsigned int m_size;        //m_size is the number of elements currently in the array.
    unsigned int m_capacity;    //m_capacity is the real allocated size for the array.



private:

    unsigned int m_allocations;
    [[deprecated("don't dare to use it boy!")]] bool m_isCapacityGreater;

    //Right now just use an typical amount.
    //Change it later using by getting the system's max stack segment size(int unix it's 8MB(usually) in Windows it's 1MB(usually))
    static const unsigned int m_maxStackSize = 1 * 1024 * 1024; //1MB == 1 * 1024 KB == 1 * 1024 * 1024 B;



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



int main()
{



CORE_LOGIC_V2("SIMD VECTOR INSTRUCTOR",


//     //see https://gist.github.com/MangaD/1fad63756ad8c946ce01dd1d52eff173 for SIMD documentation
//     std::cout << __builtin_cpu_supports("") << '\n';
//
//     std::cout << sizeof(int) << '\n';
//
// #ifdef __AVX2__
//     std::cout << "AVX2 supported!\n";
// #else
//     std::cout << "AVX2 not supported.\n";
// #endif
//



)


//TEST_STACK_FRAME()



TEST(

    unsigned long long testSize = 1000;
    //DynamicArray array(testSize);
    //array.Insert(13);

    DynamicArray array;

    // const char *a = "Hello, World!";
    // const int *b = nullptr;

Benchmark(

    for (unsigned int i=0; i<testSize; ++i)
    {
        array.Insert(i);
        //std::cout << array[i] << '\n';

    }

)

    // for (unsigned int i=0; i<testSize; ++i)
    // {
    //     std::cout << array[i] << '\n';
    // }

    //array[13] = 0;


    std::cout << "The size of the array is: " << array.Size() << '\n';;;"no issue lol";
    std::cout << "The number of allocation done is: " << array.Allocations() << '\n';

)

"no issue lol";

    int *abs = nullptr;


TEST(

    //The stackStorage will be deleted because it's storage duration is till the current 'TEST' scope.
    //Even if 'abs' has the pointer after the closing braces are executed the code underlying data of 'stackStorage' itself will be delete.
    alignas(int) unsigned char stackStorage[1024];
    abs = new(stackStorage) int(123);




    //void *heapStorage = malloc(1024*sizeof(int));


    //ptr = reinterpret_cast<int*>(heapStorage);


    //free(ptr);
    //free(heapStorage);



)


    std::cout << "The first element of abs pointer is: " << abs[0] << '\n';


TEST(

    // using namespace Container;
    //
    // LinkedList list;
    // list.Insert(10);
    //
    // std::cout << list.Last() << '\n';


)




;;;;    //giving semicolons here is not a problem





CORE_LOGIC(/*#define COMMENT_OUT_LOGIC,*/

    // int newValue = 13;
    //
    //
    // int *p = new int[2];
    //
    // p[0] = 0;
    // p[1] = 1;
    //
    //
    // int *other = new int[3];
    // other[0] = p[0];
    // other[1] = p[1];
    // other[2] = newValue;
    //
    // delete[] p;
    //
    //
    // for (auto i=0; i<3; ++i)
    // {
    //     std::cout << other[i] << '\n';
    // }
    //
    // //p = new int[4];
    // //
    // // p[0] = 0;
    // // p[1] = 1;
    // // p[2] = 2;
    // // p[3] = 3;

)



CORE_LOGIC(

    // int *p = static_cast<int*>(std::malloc(3*sizeof(int)));
    //
    // p[0] = 0;
    // p[1] = 1;
    // p[2] = 2;
    //
    // free(p+2);

)





    return 0;
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
