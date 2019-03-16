#include "gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <iostream>
#include <string>

const GLsizei LOG_SIZE = 1024;
GLchar infoLog[LOG_SIZE];

void resize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

GLuint compile(const char *source, GLenum type) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);

  GLint success;
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog(shader, LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to compile shader:\n" << infoLog;
  }

  return shader;
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

GLuint gl::compileShader(const char *vertexShader, const char *fragmentShader) {
  GLuint vs = compile(vertexShader, GL_VERTEX_SHADER);
  GLuint fs = compile(fragmentShader, GL_FRAGMENT_SHADER);

  GLuint program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to link program:\n" << infoLog;
  }

  glDeleteShader(vs);
  glDeleteShader(fs);
  return program;
}
