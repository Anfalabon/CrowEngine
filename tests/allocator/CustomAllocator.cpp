

#include <gtest/gtest.h>

#include "assets/assetManager/AssetManager.hpp"

#include <list>
#include <queue>
#include <forward_list>


class ArenaAllocator
{

public:

    ArenaAllocator() = delete;

    explicit ArenaAllocator(std::size_t n) :
        m_storage{(unsigned char*)::operator new(n)},
        //m_uStorage{(unsigned char*)::operator new(n)},
        m_offset{0},
        m_capacity{n}
    {

    }

    ~ArenaAllocator()
    {
        if (m_storage)
        {
            ::operator delete(m_storage);
        }

        m_offset = 0;
        m_capacity = 0;
    }

    void *Allocate(std::size_t n, std::size_t align = alignof(std::max_align_t))
    {
        std::size_t p = (m_offset + align - 1) & ~(align - 1);
        if (p + n > m_capacity){std::__throw_bad_alloc();}

        m_offset = p + n;

        //return m_uStorage + p;
        return m_storage + p;
    }

    void Deallocate()
    {
        if (m_storage)
        {
            ::operator delete(m_storage);
        }

        m_offset = 0;
        m_capacity = 0;
    }


    [[nodiscard]] inline std::size_t &GetCapacity(){return m_capacity;}


private:

    unsigned char *m_storage;
    std::unique_ptr<unsigned char> m_uStorage;
    std::size_t m_offset;
    std::size_t m_capacity;

};



TEST(TestAllocator, ArenaAllocatorInvalidation)
{
    ArenaAllocator arena(1000*sizeof(int));




    int *p = static_cast<int*>(arena.Allocate(100*sizeof(int)));

    for (int i = 0; i<10; ++i)
    {
        p[i] = i;
    }

    for (int i = 0; i<10; ++i)
    {
        std::cout << p[i] << '\n';
        EXPECT_EQ(p[i], i);
    }


    arena.GetCapacity() = 1000;




    //arena.Deallocate();


    std::size_t testSize = 100;
    float *p2 = static_cast<float*>(arena.Allocate(testSize*sizeof(float)));

    for (int i = 0; i<testSize; ++i)
    {
        p2[i] = 10.0424f/(i+1);
    }

    for (int i = 0; i<testSize; ++i)
    {
        std::cout << p2[i] << '\n';
        EXPECT_EQ(p2[i], 10.0424f/(i+1));
    }



}




float Q_rSqrt(float x)
{
    float xhalf = 0.5f * x;
    //int i = *(int*)&x;            // store floating-point bits in integer
    int i = std::bit_cast<int>(x);
    i = 0x5f3759df - (i >> 1);    // initial guess for Newton's method
    x = *(float*)&i;              // convert new bits into float
    x = x*(1.5f - xhalf*x*x);     // One round of Newton's method
    return x;
}



TEST(TestSTL, TestingSTL)
{

    std::list<int> l;
    std::string_view s = "";


    std::string x = "asfdkja;sldfkj";
    std::hash<std::string> hashIT;

    std::cout << hashIT(x) << '\n';


    //queue
    {
        std::queue<int> q;

        q.push(10);
        q.push(11);
        q.push(12);
        q.push(13);
        q.push(14);
        q.push(15);
        q.push(16);
        q.push(17);

        std::cout << q.front() << '\n';
        std::cout << q.size() << '\n';
    }


    //deq
    {
        std::deque<int> q;
        q.push_back(10);
        q.push_back(11);

        q.push_front(88);

        std::cout << q.front() << '\n';
    }

    //linked list
    {
        std::forward_list<int> linkedList;

        linkedList.push_front(10);
        linkedList.push_front(2122);
        linkedList.push_front(10);
        linkedList.push_front(23);

        std::cout << linkedList.remove(10) << '\n';


        // for (auto it = linkedList.cbegin(); it != linkedList.cend(); ++it)
        // {
        //     std::cout << *it << '\n';
        // }


        for (auto &element : linkedList)
        {
            ++element;
        }

        for (const auto &element : linkedList)
        {
            std::cout << element << '\n';
        }





    }





}



int main()
{

    int a = 10;
    int b = 12;

    std::cout << &a << '\n';
    std::cout << &b << '\n';


    float x = 9.0f;
    float xhalf = 0.5f * x;
    int i = std::bit_cast<int>(x);

    EXPECT_EQ(i, *(int*)&x);


    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
