file(GLOB_RECURSE CORE_SOURCES CONFIGURE_DEPENDS *.cpp)

add_library(CoreUtility STATIC ${CORE_SOURCES})
#target_include_directories(CoreUtility PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(CoreUtility PUBLIC ..)