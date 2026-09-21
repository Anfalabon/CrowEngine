file(GLOB_RECURSE GRAPHICSAPI_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(GraphicsAPI OBJECT ${GRAPHICSAPI_SOURCES})
target_include_directories(GraphicsAPI PRIVATE ..)
target_link_libraries(GraphicsAPI PRIVATE

        CoreUtility

        #external libraries
        glad
        glfw
        spdlog
        glm::glm
        imageLoader

)
