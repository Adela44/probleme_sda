cmake_minimum_required(VERSION 4.1)
project(labirint_robot C)

set(CMAKE_C_STANDARD 11)

add_executable(labirint_robot main.c)
target_compile_options(labirint_robot PRIVATE -Wall)