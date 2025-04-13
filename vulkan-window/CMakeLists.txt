cmake_minimum_required(VERSION 3.15)
project(vulkan_window CXX)

find_package(glfw3 REQUIRED)

message("Building with CMake version: ${CMAKE_VERSION}")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} "-framework OpenGL" glfw)
