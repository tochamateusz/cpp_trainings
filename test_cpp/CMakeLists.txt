cmake_minimum_required(VERSION 3.16)
project(test_cpp
    VERSION 0.0.1
    DESCRIPTION "Trying google test"
    LANGUAGES CXX
)

include(CTest)

add_subdirectory(external)
add_subdirectory(my_project)


