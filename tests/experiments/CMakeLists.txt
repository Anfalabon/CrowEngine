add_executable(TestGL testGL.cpp)

target_include_directories(TestGL PRIVATE ../../)


target_link_libraries(TestGL PRIVATE

        CoreUtility

        glad
        imageLoader
        glm
        glfw

)

