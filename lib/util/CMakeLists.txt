add_library(util STATIC
  src/window.cpp
  src/camera.cpp
  src/timer.cpp
  src/shader.cpp
  src/image.cpp
  src/fs.h
  src/stb_image.h
  include/util/gl.h)

if(WIN32)
  target_sources(util PRIVATE src/win32_fs.cpp)
elseif(APPLE)
  target_sources(util PRIVATE src/osx_fs.cpp)
endif()

target_include_directories(util PUBLIC include)
target_link_libraries(util PUBLIC glfw glad glm)
