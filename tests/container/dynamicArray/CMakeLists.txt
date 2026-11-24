


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -O0")
endif()

enable_testing()


add_executable(TestDynamicArray TestDynamicArray.cpp)
add_executable(BenchmarkDynamicArray BenchmarkDynamicArray.cpp)

target_include_directories(TestDynamicArray PUBLIC ../../..)
target_include_directories(BenchmarkDynamicArray PUBLIC ../../..)

target_link_libraries(TestDynamicArray PRIVATE
        CoreUtility
        GTest::gtest_main
        benchmark::benchmark_main
)

target_link_libraries(BenchmarkDynamicArray PRIVATE
        CoreUtility
        #GTest::gtest_main
        benchmark::benchmark_main
)


gtest_discover_tests(TestDynamicArray)
#gtest_discover_tests(BenchmarkDynamicArray)

