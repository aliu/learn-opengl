cmake_minimum_required(VERSION 3.8)
project(learn-opengl)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

add_executable(triangle triangle.cpp util/gl.cpp util/gl.h)
target_link_libraries(triangle PRIVATE glfw glad)
