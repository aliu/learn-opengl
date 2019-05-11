#include "util/gl.h"

#include <GLFW/glfw3.h>

double gl::Timer::delta() {
  double now = glfwGetTime();
  double delta = now - time;
  time = now;
  return delta;
}
