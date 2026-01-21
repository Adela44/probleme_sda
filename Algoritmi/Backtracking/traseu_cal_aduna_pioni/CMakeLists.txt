cmake_minimum_required(VERSION 4.1)
project(traseu_cal_aduna_pioni C)

set(CMAKE_C_STANDARD 11)

add_executable(traseu_cal_aduna_pioni main.c)
target_compile_options(traseu_cal_aduna_pioni PRIVATE -Wall)