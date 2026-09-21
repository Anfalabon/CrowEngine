file(GLOB_RECURSE BUFFER_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(Buffer STATIC ${BUFFER_SOURCES})
target_include_directories(Buffer PRIVATE ..)
target_link_libraries(Buffer PRIVATE

        CoreUtility

        #external libraries
        glad
        glfw
        spdlog
        glm::glm
        imageLoader

)