


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -O0")
endif()

enable_testing()


add_executable(TestDeque TestDeque.cpp)
target_include_directories(TestDeque PUBLIC ../../)

target_link_libraries(TestDeque PRIVATE
        CoreUtility
        GTest::gtest_main
        benchmark::benchmark_main
)


gtest_discover_tests(TestDeque)