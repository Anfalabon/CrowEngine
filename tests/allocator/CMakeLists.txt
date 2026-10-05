

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -O0")
endif()

enable_testing()

add_executable(TestAllocator CustomAllocator.cpp)
target_include_directories(TestAllocator PUBLIC ../../)

target_link_libraries(TestAllocator PRIVATE
        CoreUtility
        GTest::gtest_main
)

gtest_discover_tests(TestAllocator)

