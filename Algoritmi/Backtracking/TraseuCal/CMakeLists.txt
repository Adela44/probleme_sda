cmake_minimum_required(VERSION 4.1)
project(TraseuCal C)

set(CMAKE_C_STANDARD 11)

add_executable(TraseuCal main.c)
target_compile_options(TraseuCal PRIVATE -Wall)