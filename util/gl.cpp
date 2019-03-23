#include "gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <fstream>
#include <functional>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const GLsizei LOG_SIZE = 1024;
GLchar infoLog[LOG_SIZE];

void resize(GLFWwindow *window, int width, int height) {
  glViewport(0, 0, width, height);
}

std::string read(const std::string &filename) {
  std::ifstream file(filename);
  std::stringstream buffer;
  buffer << file.rdbuf();
  return buffer.str();
}

GLuint create(const std::string &filename) {
  std::string ext = filename.substr(filename.rfind('.') + 1);
  if (ext == "vert")
    return glCreateShader(GL_VERTEX_SHADER);
  if (ext == "frag")
    return glCreateShader(GL_FRAGMENT_SHADER);
  return 0;
}

GLuint compile(const std::string &filename) {
  GLuint shader = create(filename);
  std::string s = read(filename);
  const char *source = s.c_str();

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

GLuint gl::shader(const std::vector<std::string> &files) {
  GLuint program = glCreateProgram();
  std::vector<GLuint> shaders;

  for (auto &file : files) {
    GLuint shader = compile(file);
    glAttachShader(program, shader);
    shaders.push_back(shader);
  }

  glLinkProgram(program);

  GLint success;
  glGetProgramiv(program, GL_LINK_STATUS, &success);
  if (!success) {
    glGetProgramInfoLog(program, LOG_SIZE, NULL, infoLog);
    std::cerr << "Failed to link program:\n" << infoLog;
  }

  for (GLuint shader : shaders) {
    glDetachShader(program, shader);
    glDeleteShader(shader);
  }

  return program;
}
