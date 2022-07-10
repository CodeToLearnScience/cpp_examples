cmake_minimum_required(VERSION 3.0 FATAL_ERROR)
project(extern_template)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include_directories(./)

file(GLOB SOURCE_LIST "*.cpp")
add_library(lib_et STATIC ${SOURCE_LIST})
add_executable(app app.cpp)
set_property(TARGET app PROPERTY CXX_STANDARD 11)
target_link_libraries(app PRIVATE lib_et)
set(CMAKE_EXECUTABLE_SUFFIX .exe)