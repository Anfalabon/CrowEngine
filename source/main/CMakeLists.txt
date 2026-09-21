file(GLOB_RECURSE MAIN_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(Main OBJECT ${MAIN_SOURCES})
target_include_directories(Main PRIVATE ..)
target_link_libraries(Main PRIVATE

        CoreUtility

        #external libraries
        glad
        glfw
        spdlog
        glm::glm
        imageLoader

)
