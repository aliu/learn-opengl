add_library(util STATIC
  src/window.cpp
  src/shader.cpp
  src/image.cpp
  include/util/gl.h
  src/stb_image.h)

target_include_directories(util PUBLIC include)
target_link_libraries(util PUBLIC glfw glad)
