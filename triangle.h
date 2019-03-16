#include "util/window.h"

#include <glad/glad.h>
#include <string>

class Triangle : public Window {
  GLuint shader_program;
  GLuint VAO, VBO;

  void init() override;
  void draw() override;

public:
  Triangle(int width, int height, std::string title);
  ~Triangle();
};
