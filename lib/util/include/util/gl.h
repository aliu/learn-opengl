#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <initializer_list>
#include <string>

namespace gl {

struct Window {
  GLFWwindow *handle;

  Window(std::string title, int width, int height);
  ~Window();

  explicit operator bool();
};

GLuint shader(std::initializer_list<std::string> filenames);
GLuint texture2D(const std::string &filename);

} // namespace gl
