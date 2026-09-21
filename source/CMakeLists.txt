

add_subdirectory(buffer)
add_subdirectory(graphicsAPI)
add_subdirectory(main)
add_subdirectory(scene)
add_subdirectory(servers)
add_subdirectory(shader)
add_subdirectory(window)


add_executable(CrowEngine)
target_include_directories(CrowEngine PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
target_link_libraries(CrowEngine PRIVATE

        CoreUtility
        AssetManager
        Buffer
        GraphicsAPI
        Main
        Scene
        Servers
        Shader
        Window

)



#file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS *.cpp)
#
#add_executable(CrowEngine ${PROJECT_SOURCES})
#target_include_directories(CrowEngine PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
#target_link_libraries(CrowEngine PRIVATE
#
#        #in project libraries
#        CoreUtility
#        assetManager
#
#
#        #external libraries
#        glad
#        glfw
#        spdlog
#        glm::glm
#        imageLoader
#
#)



