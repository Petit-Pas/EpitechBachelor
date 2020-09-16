cmake_minimum_required(VERSION 3.9)
project(cpp_arcade)

set(CMAKE_CXX_STANDARD 11)

add_compile_options(-Wall -Wextra -W)

file(GLOB_RECURSE SOURCE_FILES ./*.cpp)
file(GLOB_RECURSE INCLUDE_FILES ./*.hpp)

include_directories(include)
include_directories(src)

add_executable(cpp_arcade ${SOURCE_FILES} ${INCLUDE_FILES} games/SolarFox/TextureSolarFox.hpp)

