file(GLOB_RECURSE SCENE_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(Scene OBJECT ${SCENE_SOURCES})
target_include_directories(Scene PRIVATE ..)
target_link_libraries(Scene PRIVATE

        CoreUtility

        #external libraries
        glad
        glfw
        spdlog
        glm::glm
        imageLoader

)