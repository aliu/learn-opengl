#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <string>

class Window {
  int width, height;
  std::string title;
  GLFWwindow *handle;

  virtual void init();
  virtual void draw();
  virtual void input(GLFWwindow *window);

public:
  Window(int width, int height, std::string title);
  virtual ~Window();
  void run();
};
