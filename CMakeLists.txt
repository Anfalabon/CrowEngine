cmake_minimum_required(VERSION 4.3)
project(CrowEngine)

set(CMAKE_CXX_STANDARD 17)


include(cmake/config/FindConfig.cmake)
include(cmake/module/FindGLFW.cmake)

add_subdirectory(source)
add_subdirectory(thirdParty)


