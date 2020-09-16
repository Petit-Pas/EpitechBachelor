##
## EPITECH PROJECT, 2018
## PSU_2017_malloc
## File description:
## Internal functions
##

cmake_minimum_required(VERSION 3.9)
project(PSU_2017_malloc)
set(CMAKE_CXX_STANDARD 11)
add_compile_options(-Wall -Wextra -W)
file(GLOB_RECURSE SOURCE_FILES src/*.c)
file(GLOB_RECURSE INCLUDE_FILES include/*.h)
include_directories(include)
include_directories(src)
add_executable(PSU_2017_malloc ${SOURCE_FILES} ${INCLUDE_FILES} src/dklqsjdljqs.c)
