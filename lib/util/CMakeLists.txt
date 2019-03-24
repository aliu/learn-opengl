project(util)

add_library(util
  src/window.cpp src/shader.cpp src/image.cpp
  include/util/gl.h include/util/stb_image.h)

target_include_directories(util PUBLIC include)
target_link_libraries(util PUBLIC glfw glad)
