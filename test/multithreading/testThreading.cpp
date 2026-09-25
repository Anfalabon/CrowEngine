

#include "core/Essentials.hpp"

#include <iostream>
#include <memory>
#include <vector>




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

    DynamicArray() : m_data(nullptr), m_size(0), m_capacity(0){}

    ~DynamicArray()
    {
        delete[] m_data;
        m_size = 0;
        m_capacity = 0;
    }

    DynamicArray(unsigned int numberOfElements) : m_size(numberOfElements)
    {
        //we can use malloc() here too
        m_data = new int[m_size];
        for (unsigned int i=0; i<m_size; ++i){m_data[i] = 0;}
    }


    void Insert(unsigned int value)
    {

        //At first increase the size by 1 as we are already going increase the size anyway.
        //Allocate memory for new array.
        //Copy all the contents of m_data(the previous one) in 'tempStorage'.
        //But remember copy exactly 'm_size-1' elements not 'm_size' because 'memcpy' has to read from the old data which still has 'm_size-1' elements(it checks the end of the old data using the given size)
        //Later assign the last element of 'tempStorage' to the new 'value' from parameter
        //Delete the old content in m_data(as it's already in 'tempStorage')
        //Make the 'm_data' point to the same starting address of tempStorage
        //As 'tempStorage' has automatic storage duration it's going to be destroyed from the current stack frame anyway
        //But the underlying data of 'tempStorage' is not going to be deleted as it's heap allocated.
        //So at the end we have only 'm_data' pointer to the content(single ownership)


        ++m_size;
        int *tempStorage = new int[m_size];

        // #pragma omp simd
        // for (unsigned int i=0; i<m_size-1; ++i)
        // {
        //     tempStorage[i] = m_data[i];
        // }

        //TODO: Add SIMD or Word-Aligned copies manually from intrinsics
        // for (unsigned int i=0; i<m_size; i+=sizeof(int))
        // {
        //     __m256 bufferVecA = _mm256_loadu_ps();
        //     __m256 bufferVecB = _mm256_loadu_ps();
        // }

        //it heavily uses SIMD or word-aligned copies for efficiency
        //See https://learnmandu.com/blog/memc/blogs/memset-memcpy-memmove-c (small blog)
        memcpy(tempStorage, m_data, (m_size-1)*sizeof(int));

        tempStorage[m_size-1] = value;

        delete[] m_data;
        m_data = tempStorage;

        //the 'tempStorage' itself is in the current stack frame so it will be deleted automatically(it has automatic storage duration).
        //but it's underlying content won't be deleted.
    }


    void RemoveLast()
    {

    }



    inline int &operator[](unsigned int index)
    {
        if (index >= m_size)
        {
            std::__throw_range_error("OUT OF BOUND ACCESS!");
        }
        return m_data[index];
    }


    inline unsigned int Size(){return m_size;}
    inline int *Data()
    {
        if (!m_data)
        {
            std::__throw_bad_exception();
        }
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
    unsigned int m_size;
    unsigned int m_capacity;

};


namespace Container
{


typedef struct Node
{
    int m_data;
    Node *m_next;
};


class LinkedList
{

public:

    //LinkedList() = default;
    ~LinkedList() = default;

    LinkedList()
    {
        m_current->m_data = 0;
        m_current->m_next = nullptr;
    }


    void Insert(int value)
    {
        if (!m_current){return;}

        m_current->m_data = value;
        m_current->m_next = nullptr;
    }

private:

    Node *m_current;


};




}


int main()
{


TEST(

    unsigned int testSize = 10'000;
    DynamicArray array(testSize);
    //array.Insert(13);

    for (unsigned int i=0; i<testSize; ++i)
    {
        std::cout << array[i] << '\n';;
    }

    std::cout << "The size of the array is: " << array.Size() << '\n';;;;

)



TEST(

    using namespace Container;

    LinkedList list;
    list.Insert(10);




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
