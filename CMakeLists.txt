cmake_minimum_required(VERSION 3.20)
project(Hazel_Engine VERSION 0.0.1)
#CPP标准
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 23)
#输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)

#debug release 后缀名
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_RELEASE_POSTFIX "_r")
#导入包
if (${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang)
    set(WHICH_COMPILER clang)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(WHICH_COMPILER gcc)
endif ()
#根据编译器不同决定库不同
set(spdlog_DIR /Volumes/Disi1lusion/Repository/CPP/libs/spdlog/${WHICH_COMPILER}/lib/cmake/spdlog)
find_package(spdlog REQUIRED)
set(fmt_DIR /Volumes/Disi1lusion/Repository/CPP/libs/fmt/lib/cmake/fmt)
find_package(fmt REQUIRED)
find_package(GLFW3 REQUIRED)
set(glad_DIR /Volumes/Disi1lusion/Repository/CPP/libs/glad)
find_package(glad REQUIRED )
set(LIBRARY_LIST
        spdlog::spdlog
        fmt::fmt
        glfw
        glad::glad
        )
link_libraries(${LIBRARY_LIST})
#头文件目录
set(HAZEL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Hazel/src)
#添加子目录
add_subdirectory(${CMAKE_SOURCE_DIR}/Hazel)
add_subdirectory(${CMAKE_SOURCE_DIR}/SandBox)
#debug release 后缀名
#set_target_properties(${TARGET_NAME} PROPERTIES DEBUG_POSTFIX "_d")
#set_target_properties(${TARGET_NAME} PROPERTIES RELEASE_POSTFIX "_r")

