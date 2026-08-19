file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS *.cpp)

add_executable(CrowEngine ${PROJECT_SOURCES})
target_include_directories(CrowEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CrowEngine PRIVATE
        glad
        glfw)
