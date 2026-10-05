#file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -O0")
endif()


enable_testing()


#add_executable(TestModelLoader ${TEST_SOURCES})
add_executable(TestModelLoader ModelLoader.cpp)

target_link_libraries(TestModelLoader PRIVATE

        CoreUtility
        GTest::gtest_main
        spdlog

)


include(GoogleTest)
gtest_discover_tests(TestModelLoader)
#gtest_discover_tests(${TEST_SOURCES})
#gtest_discover_tests(ModelLoader.cpp)
