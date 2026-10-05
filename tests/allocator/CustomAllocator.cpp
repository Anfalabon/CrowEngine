

#include <gtest/gtest.h>

#include "assets/assetManager/AssetManager.hpp"


class ArenaAllocator
{

public:

    ArenaAllocator() = delete;

    explicit ArenaAllocator(std::size_t n) :
        m_storage{(unsigned char*)::operator new(n)},
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

    void *allocate(std::size_t n, std::size_t align = alignof(std::max_align_t))
    {
        std::size_t p = (m_offset + align - 1) & ~(align - 1);
        if (p+n > m_capacity)
        {
            std::__throw_bad_alloc();
        }

        m_offset = p + n;

        return m_storage + p;
    }


    [[nodiscard]] inline std::size_t GetCapacity(){return m_capacity;}


private:

    unsigned char *m_storage;
    std::size_t m_offset;
    std::size_t m_capacity;

};



TEST(TestAllocator, ArenaAllocatorInvalidation)
{
    ArenaAllocator arena(100*sizeof(int));
    int *p = static_cast<int*>(arena.allocate(100*sizeof(int)));

    for (int i = 0; i<10; ++i)
    {
        p[i] = i;
    }

    for (int i = 0; i<10; ++i)
    {
        std::cout << p[i] << '\n';
        EXPECT_EQ(p[i], i);
    }


    int *p2 = static_cast<int*>(arena.allocate(100*sizeof(int)));

    for (int i = 0; i<10; ++i)
    {
        p2[i] = i;
    }

    for (int i = 0; i<10; ++i)
    {
        std::cout << p2[i] << '\n';
        EXPECT_EQ(p2[i], i);
    }



}




int main()
{
    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
