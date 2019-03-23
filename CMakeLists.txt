cmake_minimum_required(VERSION 3.8)
project(learn-opengl)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

add_subdirectory(lib/glfw)
add_subdirectory(lib/glad)

set_target_properties(glfw PROPERTIES FOLDER lib)
set_target_properties(glad PROPERTIES FOLDER lib)

add_custom_target(copy_resources ALL
  COMMAND ${CMAKE_COMMAND} -E copy_directory ${CMAKE_CURRENT_SOURCE_DIR}/res
  ${CMAKE_BINARY_DIR}/res)

add_executable(triangle triangle.cpp util/gl.cpp util/gl.h)
target_link_libraries(triangle PRIVATE glfw glad)
