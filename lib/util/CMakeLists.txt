project(util)

add_library(util src/window.cpp src/shader.cpp include/util/gl.h)
target_include_directories(util PUBLIC include)
target_link_libraries(util PUBLIC glfw glad)
