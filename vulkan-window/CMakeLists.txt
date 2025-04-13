cmake_minimum_required(VERSION 3.15)
project(vulkan_window CXX)
set(CMAKE_CXX_STANDARD 17)

set(glm_DIR "./build/Release/generators")

find_package(Vulkan REQUIRED)
find_package(glfw3 REQUIRED)
find_package(glm REQUIRED)

include_directories(${PROJECT_NAME} PUBLIC "./external/include")

message("Building with CMake version: ${CMAKE_VERSION}")

add_executable(${PROJECT_NAME} src/main.cpp)
target_link_libraries(${PROJECT_NAME} "-framework OpenGL" Vulkan::Vulkan glfw glm::glm)
