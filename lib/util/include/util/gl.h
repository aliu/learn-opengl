#pragma once

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <initializer_list>
#include <string>
#include <utility>

struct GLFWwindow;

namespace gl {

struct Camera {
  glm::vec3 position;
  double pitch, yaw;
  glm::mat4 view();
  void move(glm::vec3 direction);
  void orient(glm::vec3 front);
};

struct Timer {
  double time = 0;
  double delta();
};

class Window {
  Camera camera;
  Timer timer;
  GLFWwindow *handle;
  std::pair<double, double> mouse;

public:
  Window(std::string title, int width, int height);
  Window(const Window &other) = delete;
  Window &operator=(const Window &other) = delete;
  ~Window();

  double update();
  void render();

  std::pair<int, int> getSize();
  glm::mat4 getView();

  void setCamera(glm::vec3 position, glm::vec3 front);
  explicit operator bool();
};

GLuint shader(std::initializer_list<std::string> filenames);
GLuint texture2D(const std::string &filename);

} // namespace gl
