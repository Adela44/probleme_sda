cmake_minimum_required(VERSION 4.1)
project(TraseuCalMax C)

set(CMAKE_C_STANDARD 11)

add_executable(TraseuCalMax main.c)
target_compile_options(TraseuCalMax PRIVATE -Wall)