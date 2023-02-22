cmake_minimum_required(VERSION 3.20)
project(Hazel_SandBox)
set(CMAKE_CXX_STANDARD_REQUIRED 20)
set(CMAKE_CXX_STANDARD 20)
#输出目录
set(EXECUTABLE_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)
set(LIBRARY_OUTPUT_PATH ${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT_NAME}/)

include_directories(${HAZEL_INCLUDE_DIRS})
add_executable(Sandbox src/SandBoxApp.cpp)
target_link_libraries(Sandbox Hazel)
set(INSTALL_LOCATION /Volumes/Disi1lusion/Repository/CPP/libs)
set(CMAKE_INSTALL_PREFIX ${INSTALL_LOCATION})