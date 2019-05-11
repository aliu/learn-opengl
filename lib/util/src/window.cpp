#include "util/gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <algorithm>
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
  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

  glfwSwapInterval(1);
  glfwSetFramebufferSizeCallback(handle, resize_callback);
  glfwSetInputMode(handle, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwGetCursorPos(handle, &mouse.first, &mouse.second);
}

gl::Window::~Window() {
  glfwDestroyWindow(handle);
  glfwTerminate();
}

double gl::Window::update() {
  double delta = timer.delta();

  double x, y;
  glfwGetCursorPos(handle, &x, &y);
  double dx = x - mouse.first;
  double dy = y - mouse.second;
  mouse = {x, y};

  camera.yaw += (8 * delta) * dx;
  camera.pitch -= (8 * delta) * dy;
  camera.pitch = std::clamp(camera.pitch, -89.0, 89.0);

  glm::vec3 direction = glm::vec3(0.0f, 0.0f, 0.0f);
  if (glfwGetKey(handle, GLFW_KEY_W) == GLFW_PRESS) direction.z += 1.0f;
  if (glfwGetKey(handle, GLFW_KEY_S) == GLFW_PRESS) direction.z -= 1.0f;
  if (glfwGetKey(handle, GLFW_KEY_D) == GLFW_PRESS) direction.x += 1.0f;
  if (glfwGetKey(handle, GLFW_KEY_A) == GLFW_PRESS) direction.x -= 1.0f;
  if (glfwGetKey(handle, GLFW_KEY_SPACE) == GLFW_PRESS) direction.y += 1.0f;
  if (glfwGetKey(handle, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) direction.y -= 1.0f;
  camera.move((float)(4 * delta) * direction);

  if (glfwGetKey(handle, GLFW_KEY_ESCAPE) == GLFW_PRESS)
    glfwSetWindowShouldClose(handle, true);

  return delta;
}

void gl::Window::render() {
  glfwSwapBuffers(handle);
  glfwPollEvents();
}

std::pair<int, int> gl::Window::getSize() {
  int width, height;
  glfwGetFramebufferSize(handle, &width, &height);
  return {width, height};
}

glm::mat4 gl::Window::getView() {
  return camera.view();
}

void gl::Window::setCamera(glm::vec3 position, glm::vec3 front) {
  camera.position = position;
  camera.orient(front);
}

gl::Window::operator bool() {
  return !glfwWindowShouldClose(handle);
}
