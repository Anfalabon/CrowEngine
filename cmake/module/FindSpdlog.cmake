
#set(LOCAL_LOGGING_DEP_DIR "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/logger/spdlog")
if(EXISTS "${CMAKE_CURRENT_SOURCE_DIR}/../../thirdParty/logger/spdlog/CMakeLists.txt")
    message(STATUS "THE LOGGING DEPENDENCY ALREADY EXISTS!")

else()

    message(STATUS "THE LOGGING DEPENDENCY IS NOT LOCAL. THEREFORE FETCHING IT FROM GIT")
    include(FetchContent)
    FetchContent_Declare(
        spdlog
        GIT_REPOSITORY https://github.com/gabime/spdlog.git
        #GIT_TAG 3.7
    )
    FetchContent_MakeAvailable(spdlog)

endif()



