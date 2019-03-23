#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <functional>
#include <string>
#include <vector>

namespace gl {

struct Options {
  std::string title;
  int width = 500, height = 500;
};

void run(Options options, std::function<void()> init,
         std::function<void(GLFWwindow*)> loop, std::function<void()> cleanup);

GLuint shader(const std::vector<std::string> &files);

} // namespace gl
