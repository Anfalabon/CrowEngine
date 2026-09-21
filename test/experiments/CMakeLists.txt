add_executable(experimentalGL testGL.cpp)

target_include_directories(experimentalGL PRIVATE ../../source)


target_link_libraries(experimentalGL PRIVATE

        glad
        imageLoader
        glm
        glfw
#        assimp
#        irrKlang

        CoreUtility

)

