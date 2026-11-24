add_subdirectory(glad)
#add_subdirectory(glfw-3.5.1)
add_subdirectory(imageLoader)
add_subdirectory(benchmark)

if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/logger/spdlog")
    message(STATUS "THE LOGGING DEPENDENCY ALREADY EXISTS!")
    #add_subdirectory(logger/spdlog)
endif()

