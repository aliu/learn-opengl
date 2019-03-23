project(util)

add_library(util src/gl.cpp include/util/gl.h)
target_include_directories(util PUBLIC include)
target_link_libraries(util PUBLIC glfw glad)
