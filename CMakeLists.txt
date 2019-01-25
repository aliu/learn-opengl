cmake_minimum_required(VERSION 3.7)

project(learn-opengl)

set(CMAKE_CXX_STANDARD 14)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(lib/glfw)

include_directories(glad/include)
add_executable(learn-opengl glad/src/glad.c main.cpp triangle.cpp)

target_link_libraries(learn-opengl glfw)
