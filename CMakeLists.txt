cmake_minimum_required(VERSION 3.24)
project(opengl3d)

set(CMAKE_CXX_STANDARD 17)

add_executable(opengl3d main.cpp)
target_link_libraries(opengl3d -lOpenGL32 -lfreeGlut)
