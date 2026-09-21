add_library(imageLoader STATIC stb_image.cpp)
target_include_directories(imageLoader PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})