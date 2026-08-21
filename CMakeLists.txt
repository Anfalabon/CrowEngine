cmake_minimum_required(VERSION 4.3)
project(CrowEngine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


include(cmake/config/FindConfig.cmake)
include(cmake/module/FindGLFW.cmake)
include(cmake/module/FindSpdlog.cmake)

add_subdirectory(source)
add_subdirectory(core)
add_subdirectory(thirdParty)




