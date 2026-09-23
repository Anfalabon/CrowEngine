

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -O0")
endif()

file(GLOB_RECURSE TEST_MULTITHREADING_SOURCES CONFIGURE_DEPENDS *.cpp)
add_executable(TestMultithreading ${TEST_MULTITHREADING_SOURCES})
target_include_directories(TestMultithreading PUBLIC ../../)
#target_link_libraries(TestMultithreading PRIVATE CoreUtility)

