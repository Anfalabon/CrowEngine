file(GLOB_RECURSE ASSETS_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(AssetManager STATIC ${ASSETS_SOURCES})
target_include_directories(AssetManager PUBLIC ..)