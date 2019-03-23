#include "util/gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <string>

void resize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

void gl::run(gl::Options options, std::function<void()> init,
             std::function<void(GLFWwindow*)> loop,
             std::function<void()> cleanup) {
  glfwInit();
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#ifdef __APPLE__
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

  GLFWwindow *window = glfwCreateWindow(options.width, options.height,
                                        options.title.c_str(), NULL, NULL);
  if (window == NULL) {
    std::cerr << "Failed to create GLFW window\n";
  }

  glfwMakeContextCurrent(window);
  glfwSetFramebufferSizeCallback(window, resize);

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    std::cerr << "Failed to initialize GLAD\n";
  }

  init();
  while (!glfwWindowShouldClose(window)) {
    loop(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }
  cleanup();
  glfwTerminate();
}
