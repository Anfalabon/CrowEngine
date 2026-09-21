file(GLOB_RECURSE TEST_MULTITHREADING_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(TestMultithreading ${TEST_MULTITHREADING_SOURCES})
#target_link_libraries(TestMultithreading PRIVATE CoreUtility)

