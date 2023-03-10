cmake_minimum_required(VERSION 3.20)
project(Hazel_Engine VERSION 0.0.1)
#CPP标准
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 23)
#输出目录
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
#set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
#set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
#修改默认包位置
set(HOMEBREW_PREFIX "/opt/homebrew")
set(CMAKE_PREFIX_PATH "${HOMEBREW_PREFIX}")
#导入包
if (${CMAKE_CXX_COMPILER_ID} STREQUAL AppleClang OR ${CMAKE_CXX_COMPILER_ID} STREQUAL Clang)
    set(WHICH_COMPILER clang)
elseif (${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    set(WHICH_COMPILER gcc)
endif ()
#根据编译器不同决定库不同
#OpenGL FrameWork
find_package(GLFW3 REQUIRED)
set(glad_DIR /Volumes/Disi1lusion/Repository/CPP/libs/glad)
find_package(glad REQUIRED)
set(glm_DIR /Volumes/Disi1lusion/Repository/CPP/libs/glm/cmake/glm)
find_package(glm REQUIRED)
#LOG FrameWork
set(spdlog_DIR /Volumes/Disi1lusion/Repository/CPP/libs/spdlog/${WHICH_COMPILER}/lib/cmake/spdlog)
find_package(spdlog REQUIRED)
set(fmt_DIR /Volumes/Disi1lusion/Repository/CPP/libs/fmt/lib/cmake/fmt)
find_package(fmt REQUIRED)
#UI FrameWork
set(imgui_DIR /Volumes/Disi1lusion/Repository/CPP/libs/imgui)
find_package(imgui REQUIRED)

set(LIBRARY_LIST
        spdlog::spdlog
        fmt::fmt
        glfw
        glad::glad
        imgui::imgui
        glm::glm
        )
link_libraries(${LIBRARY_LIST})
#头文件目录
set(HAZEL_INCLUDE_DIRS ${CMAKE_SOURCE_DIR}/Hazel/src)
#debug release 后缀名
set(CMAKE_DEBUG_POSTFIX "_d")
set(CMAKE_RELEASE_POSTFIX "_r")
#添加子目录
add_subdirectory(${CMAKE_SOURCE_DIR}/Hazel)
add_subdirectory(${CMAKE_SOURCE_DIR}/SandBox)
#安装目录
set(INSTALL_LOCATION /Volumes/Disi1lusion/Repository/CPP/libs)
set(CMAKE_INSTALL_PREFIX ${INSTALL_LOCATION})