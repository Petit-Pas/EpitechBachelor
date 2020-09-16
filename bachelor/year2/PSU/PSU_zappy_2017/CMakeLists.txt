cmake_minimum_required(VERSION 3.10)
project(zappy C CXX)

set(CMAKE_CXX_STANDARD 14)

include_directories(./src/server/include)
include_directories(./src/clients/Graphical/include)
include_directories(./src/clients/Graphical/ImGUI/include)

find_package(OpenGL)

file(GLOB_RECURSE SERVER_SOURCES ./src/server/*.c)
file(GLOB_RECURSE SERVER_INCLUDES ./src/server/include/*.h)
file(GLOB_RECURSE GRAPHICAL_SOURCES ./src/clients/Graphical/src/*.cpp)
file(GLOB_RECURSE GRAPHICAL_INCLUDES ./src/clients/Graphical/include/*.hpp)
file(GLOB_RECURSE IMGUI_SOURCES ./src/clients/Graphical/ImGUI/src/*.cpp)
file(GLOB_RECURSE IMGUI_INCLUDES ./src/clients/Graphical/ImGUI/include/*.h)

add_executable(spectate ${GRAPHICAL_SOURCES} ${GRAPHICAL_INCLUDES} ${IMGUI_SOURCES} ${IMGUI_INCLUDES})
add_executable(zappy_server ${SERVER_SOURCES} ${SERVER_INCLUDES})


target_compile_options(zappy_server PUBLIC "-W" PUBLIC "-Wall" PUBLIC "-Wextra" PUBLIC "-pedantic" PUBLIC "-Iinclude")
target_compile_options(spectate PUBLIC "-W" PUBLIC "-Wall" PUBLIC "-Wextra" PUBLIC "-Iinclude" "-g")

target_link_libraries(zappy_server m)
target_link_libraries(spectate sfml-graphics sfml-window sfml-system ${OPENGL_LIBRARIES})







