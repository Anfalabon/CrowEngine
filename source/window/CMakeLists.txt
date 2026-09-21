file(GLOB_RECURSE WINDOW_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(Window OBJECT ${WINDOW_SOURCES})
target_include_directories(Window PRIVATE ..)
target_link_libraries(Window PRIVATE

        CoreUtility

        #external libraries
        glad
        glfw
        spdlog
        glm::glm
        imageLoader

)
