file(GLOB_RECURSE SHADER_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(Shader OBJECT ${SHADER_SOURCES})
target_include_directories(Shader PRIVATE ..)
target_link_libraries(Shader PRIVATE

        CoreUtility

        #external libraries
        glad
        glfw
        spdlog
        glm::glm
        imageLoader

)
