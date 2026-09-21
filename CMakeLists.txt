cmake_minimum_required(VERSION 4.1)
project(CrowEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address,undefined,leak -fno-omit-frame-pointer -g -O0")
endif()


include(cmake/config/FindConfig.cmake)
include(cmake/module/FindGLFW.cmake)
include(cmake/module/FindSpdlog.cmake)
include(cmake/module/FindGLM.cmake)
#include(cmake/module/FindGoogleTest.cmake)

add_subdirectory(source)
add_subdirectory(core)
add_subdirectory(assets)
add_subdirectory(thirdParty)
add_subdirectory(test)




