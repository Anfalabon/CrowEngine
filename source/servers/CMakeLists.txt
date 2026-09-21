file(GLOB_RECURSE SERVERS_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(Servers OBJECT ${SERVERS_SOURCES})
target_include_directories(Servers PRIVATE ..)
target_link_libraries(Servers PRIVATE

        CoreUtility

        #external libraries
        glad
        glfw
        spdlog
        glm::glm
        imageLoader

)
