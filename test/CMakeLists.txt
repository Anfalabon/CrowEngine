file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(CrowEngineTest ${TEST_SOURCES})

target_include_directories(CrowEngineTest PUBLIC ${CMAKE_CURRENT_SOURCE_DIR} ../core)
target_link_libraries(CrowEngineTest PUBLIC CoreUtility)