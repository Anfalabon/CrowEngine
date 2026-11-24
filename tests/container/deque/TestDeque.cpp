
#include "gtest/gtest.h"

#include "core/Essentials.hpp"

#include <iostream>
#include <deque>
#include <memory>








template<typename T, unsigned int templatePointers = 7, unsigned int templateBlockSize = 4>
class Deque
{
public:

    //typedef typename T value_type;

    Deque() : m_pointers(templatePointers), m_blockSize(templateBlockSize)
    {
        //Hey can we run other member functions even before constructor does it's job?
        //OH the constructor is already running.
        //m_map = this->AllocMap();

        //PreAllocate some pointers and blocks
        m_map = new T*[m_pointers];

        m_size = 0;
        m_capacity = m_pointers * m_blockSize;

        for (std::size_t i = 0; i<m_pointers; ++i)
        {
            m_map[i] = new T[m_blockSize];
        }


    }

    ~Deque()
    {
        this->DeallocMap(m_pointers);
    }


    Deque(Deque &&other)
    {
        CrowEngine::Logging::print("Move Constructor Called!\n");
    }

    Deque &operator=(Deque &&other)
    {
        CrowEngine::Logging::print("Move Assignment Called!");
        return *this;
    }


    //This is allowed in C++=20
    auto GetValue()
    {
        struct MultipleValue
        {
            unsigned int m_value;
            std::string m_string;
        };

        return MultipleValue{12, "Hey!"};
    }


    struct MultipleValue;
    //using type = MultipleValue;
    MultipleValue GetValue2()
    {
        struct MultipleValue
        {
            unsigned int m_value;
            std::string m_string;

            class Deque *ptr;
        };

        return MultipleValue{12, "Hey!"};
    }




    T **AllocMap(unsigned int pointers)
    {
        T **tempMap = new T*[pointers];
        for (std::size_t i = 0; i<pointers; ++i)
        {
            tempMap[i] = new T[m_blockSize];
        }
        // for (T *p : tempMap)
        // {
        //     p = new T[m_blockSize];
        // }
        return tempMap;
    }

    void DeallocMap(const std::size_t pointers)
    {
        //#pragma omp parallel for
        for (std::size_t i=0; i<pointers; ++i)
        {
            delete[] m_map[i];
        }
        delete[] m_map;
        m_map = nullptr;
    }




    [[nodiscard]] inline unsigned int Pointers()
    {
        return m_pointers;
    }

    [[nodiscard]] inline unsigned int BlockSize()
    {
        return m_blockSize;
    }

    [[nodiscard]] inline unsigned int Size()
    {
        return m_blockSize;
    }

    [[nodiscard]] inline unsigned int Capacity()
    {
        return m_pointers * m_blockSize;
    }





    //TODO: Bad name. Fix it!
    T **AllocateInitializedBlock()
    {
        unsigned int oldPointers = m_pointers;
        ++m_pointers;
        m_capacity = m_pointers * m_blockSize;  //We can also say it as 'm_capacity += m_blockSize' maybe.

        T **tempMap = this->AllocMap(m_pointers);

        //TODO: Use 'memcpy()' here for better performence.
        //memcpy(tempMap, m_map, m_);

        //memcpy(tempMap, m_map, m_size*sizeof(T));
        for (std::size_t i=0; i<m_size; ++i)
        {
            //It migth do copy depending on what the type 'T' is.
            //tempMap[i/m_blockSize][i%m_blockSize] = std::move(m_map[i/m_blockSize][i%m_blockSize]);
            tempMap[i/m_blockSize][i%m_blockSize] = m_map[i/m_blockSize][i%m_blockSize];
        }

        return tempMap;
    }




    [[deprecated("This is the old deprecated of Insert() function!")]] void InsertV1()
    {
        // unsigned int oldPointers = m_pointers;
        // ++m_pointers;
        // m_capacity = m_pointers * m_blockSize;  //We can also say it as 'm_capacity += m_blockSize' maybe.
        // T **tempMap = new T*[m_pointers];
        //
        // //TODO: Use 'memcpy()' here for better performence.
        // //memcpy(tempMap, m_map, m_);
        // for (std::size_t i = 0; i<m_pointers; ++i)
        // {
        //     tempMap[i] = new T[m_blockSize];
        // }
        //
        // for (std::size_t i=0; i<m_size; ++i)
        // {
        //     //It migth do copy depending on what the type 'T' is.
        //     tempMap[i/m_blockSize][i%m_blockSize] = m_map[i/m_blockSize][i%m_blockSize];
        // }

        // ++m_size;
        // unsigned int index = m_size - 1;
        // tempMap[index/m_blockSize][index%m_blockSize] = value;

        // if (!m_map){return;}
        // //Previously we increased the number of pointers by '++m_pointers'.
        // //So we need to do 'm_pointers-1' here.
        // for (std::size_t i=0; i<oldPointers; ++i)
        // {
        //     delete[] m_map[i];
        // }
        // delete[] m_map;
        //
        // m_map = tempMap;
    }




    void Insert(const T &value)
    {
        if (m_size < m_capacity)
        {
            ++m_size;
            unsigned int index = m_size - 1;
            m_map[index/m_blockSize][index%m_blockSize] = value;
            return;
        }

        CrowEngine::Logging::print("Allocating and Initializing block...\n");
        //the 'F' suffix here stands for 'returned from 'F'ucntion.
        T **tempMapF = this->AllocateInitializedBlock();


        ++m_size;
        unsigned int index = m_size - 1;
        tempMapF[index/m_blockSize][index%m_blockSize] = value;

        if (!m_map){return;}
        //Previously we increased the number of pointers by '++m_pointers'.
        //So we need to do 'm_pointers-1' or 'oldPointers' here.
        unsigned int oldPointers = m_pointers - 1;
        this->DeallocMap(oldPointers);

        m_map = tempMapF;
        CrowEngine::Logging::print("Allocated and initialized a Block!\n");
    }


    unsigned int Remove() & //Or &&
    {
	    if(unsigned int var = 10; var == 10)
	    {
	        std::cout << "The value of var is :" << var << '\n';
	        return var;
	    }
	
        return -1;
    }


    T &operator[](const std::size_t index)
    {
        if (index < 0 && index >= m_size) [[unlikely]]
        {
            std::__throw_out_of_range("OUT OF BOUND ACCESS!");
            //return T();
            //Here it's an rvalue then how it's binding to lvalue reference(T &operator)?
            //Is it taking some sort of assumption that 'T' is going to be 'const T'?
        }
        return m_map[index/m_blockSize][index%m_blockSize];
    }

										
    inline T &ValueAt(const std::size_t index)
    {
        // To think that [[unlikely]] helps the branch predictor is a Fool wise man            		        
        if (index < 0 && index > m_pointers*m_blockSize) [[unlikely]]
        {
            std::__throw_out_of_range("OUT OF BOUND ACCESS!");
            return T{}; //No worries RVO is with you!
        }
        return m_map[index/m_blockSize][index%m_blockSize];
    }






private:

    T **m_map;

    //We will be using these in the future but for now "T **m_map" just works.
    //DynamicArray<>
    std::vector<std::vector<T>> m_vecMap;
    std::unique_ptr<std::unique_ptr<T>> m_uniqueMap;
    std::shared_ptr<T> m_sharedPointer;
    

    unsigned int m_size;
    unsigned int m_capacity;

private:

    unsigned int m_pointers;
    const unsigned int m_blockSize = 4;

    unsigned int m_pointersSize;
    unsigned int m_pointersCapacity;


};





namespace CrowEngine
{


template<typename T>
struct RemoveReference
{
    using type = T;
};

template<typename T>
struct RemoveReference<T&>   //If we do <T&> here then it's a partial specialization.
{
    using type = T;
};

template<typename T>
struct RemoveReference<T&&>   //If we do <T&> here then it's a partial specialization.
{
    using type = T;
};

//Why should we Add 'constexpr'?
template<typename T>
__attribute__((always_inline)) inline
constexpr typename RemoveReference<T>::type&& RvalueCast(T &&value) noexcept
{
    return static_cast<typename RemoveReference<T>::type&&>(value);
}



//Just here checking for the 'extern' keyword.
extern unsigned int GetUnsignedInt(){return 10;}
extern const char *GetStr(){return "Hello, World!";}
extern void *GetMalloc(){return malloc(10);}


}




TEST(CustomDequeTest, TestInsertion)
{
    std::deque<int> deqSTL;


    Deque<int, 7, 512> deq;

    unsigned int testSize = 2 * 7*512;

    for (std::size_t i=0; i<testSize; ++i)
    {
        deq.Insert(static_cast<int>(i));
    }

    //Deque<int, 7, 512> deq2 = static_cast<typename RemoveReference<int, 7, 512>::type&&>(deq);

    Deque<int, 7, 512> deq2;// = CrowEngine::RvalueCast(deq);
    deq2 = CrowEngine::RvalueCast(deq);


    for (std::size_t i=0; i<testSize; ++i)
    {
        std::cout << deq[i] << '\n';
        EXPECT_EQ(deq[i], i);
    }
}




TEST(TestMemcpy, DISABLED_TestingMemcpyBugs)
{

    int *p;
    int *arr = new int[10];

    for (unsigned int i=0; i<10; ++i){arr[i] = i;}

    memcpy(p, arr, 10*sizeof(int));

    for (unsigned int i=0; i<10; ++i)
    {
        std::cout << p[i] << '\n';
    }

    for (unsigned int i=0; i<10; ++i)
    {
        std::cout << arr[i] << '\n';
    }

    //We can't delete a pointer that wasn't allocated by new.
    //delete[] p;
    delete[] arr;

}



long double operator""_km(long double km)
{
    return 1000.0 * km;
}


struct A
{

public:

    A(int value)
    {
        m_number = value;
        std::cout << m_number << '\n';
    }

    A(const int &value)
    {
        m_number = value;
        std::cout << m_number << '\n';
    }

public:

    //B m_obj;
    //Here if m_obj is constructed here directly not in the member initializer list then the constructor run here.
    //If the m_obj is initialized in the member initialzer list then the constructor here isn't run rather it's run in the member initializer list site.
    //So i guess the compiler actually checks if it was initialized here directly. If not then in member initializer list? If no then just run the constructor at declaration site
    //If yes then construct it in the member initializer list.
    //If not in the member initializer list but in the constructor body then it constructs it two times. First directly in the declaration site next in the constructor body.

    int m_number;
};



void func(const char*){ std::cout << "Ran the const char* one!" << '\n';}
void func(short){ std::cout << "Ran the short one!" << '\n';}


TEST(TestOutOfTheBox, OutOfTheBoxTesting)
{
    unsigned int value = CrowEngine::function();
    std::cout << "The value of value is: " << value << '\n';

    //std::allocator<int> value;
    // int *p = value.allocate(10);
    // value.deallocate(p, 10);

    int a = 10;
    int *ptr = __builtin_addressof(a);

    //CrowEngine::function();
    std::cout << CrowEngine::GetUnsignedInt() << '\n';
    std::cout << 10.0_km << '\n';

    //A obj(10);

    //func(0);

    //(void*)0;

    //wchar_t

    __asm__ volatile("mov $64, %%rax;"
                 "mov $0, %%rdi;"
                 "syscall" : : : "rax", "rdi");



}


// __asm__ volatile ("mov $60, %%rax; mov $0, %%rdi; syscall" : : : "rax", "rdi");
// extern "C" void _start(){
//     __asm__ volatile("mov $64, %%rax;"
//                      "mov $0, %%rdi;"
//                      "syscall" : : : "rax", "rdi");
// }


int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}

