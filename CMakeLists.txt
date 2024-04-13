cmake_minimum_required(VERSION 3.6.0)
project(hello_window VERSION 1.0.0)
list(APPEND CMAKE_PREFIX_PATH "/opt/homebrew")

find_package(GLFW3 REQUIRED)
find_package(OpenGL REQUIRED)


add_executable(hello_window src/config.h src/main.cpp src/glad.c)

target_include_directories(hello_window PRIVATE dependencies)

target_link_libraries(hello_window glfw OpenGL::GL)
