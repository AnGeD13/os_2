cmake_minimum_required(VERSION 3.10.0)

project(Background_process)

add_library(background_process STATIC background_process.cpp)

add_executable(main main.cpp)
add_executable(subprogram subprogram.cpp)

target_link_libraries(main background_process)
