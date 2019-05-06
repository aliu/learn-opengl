#include "util/gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <string>

void resize_callback(GLFWwindow *handle, int width, int height) {
  glViewport(0, 0, width, height);
}

void error_callback(int error, const char *description) {
  std::cerr << "Error: " << description << '\n';
}

gl::Window::Window(std::string title, int width, int height) {
  glfwSetErrorCallback(error_callback);

  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);

  glfwMakeContextCurrent(handle);
  glfwSetFramebufferSizeCallback(handle, resize_callback);

  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
}

gl::Window::~Window() {
  glfwDestroyWindow(handle);
  glfwTerminate();
}

gl::Window::operator bool() {
  return !glfwWindowShouldClose(handle);
}
