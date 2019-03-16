#include "window.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

void resize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void Window::init() {}
void Window::draw() {}

void Window::input(GLFWwindow *window) {
  if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
    glfwSetWindowShouldClose(window, true);
  }
}

Window::Window(int width, int height, std::string title)
    : width(width), height(height), title(title) {}

Window::~Window() {
  glfwDestroyWindow(handle);
  glfwTerminate();
}

void Window::run() {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  handle = glfwCreateWindow(width, height, title.c_str(), NULL, NULL);
  if (handle == NULL) {
    throw std::runtime_error("Failed to create GLFW window");
  }
  glfwMakeContextCurrent(handle);
  glfwSetFramebufferSizeCallback(handle, resize);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    throw std::runtime_error("Failed to initialize GLAD");
  }

  init();

  while (!glfwWindowShouldClose(handle)) {
    input(handle);
    draw();
    glfwSwapBuffers(handle);
    glfwPollEvents();
  }
}
