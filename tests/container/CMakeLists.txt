

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -O0")
endif()

enable_testing()

add_executable(TestContainer TestContainer.cpp)
target_include_directories(TestContainer PUBLIC ../../)

target_link_libraries(TestContainer PRIVATE
        CoreUtility
        GTest::gtest_main
)

gtest_discover_tests(TestContainer)

