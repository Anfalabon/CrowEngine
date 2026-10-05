

#include <gtest/gtest.h>

#include "assets/assetManager/AssetManager.hpp"


class ArenaAllocator
{

public:

    ArenaAllocator() = default;
    ~ArenaAllocator() = default;

    // void *allocate(std::size_t n, std::size_t align = alignof(std::max_align_t))
    // {
    //     m_storage = (unsigned char*)::operator new;
    //     m_offset = 0;
    // }


private:

    unsigned char *m_storage;
    std::size_t m_offset;
    std::size_t m_bump;

};



// TEST()
// {
//
// }



int main()
{
    ArenaAllocator arena;

    std::cout << CrowEngine::AssetManager::ExecutableDir() << '\n';



    testing::InitGoogleTest();
    return RUN_ALL_TESTS();
}
