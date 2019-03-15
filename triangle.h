#include "window.h"

#include <string>

class Triangle : public Window {
  unsigned int shader_program;
  unsigned int VAO, VBO;

  void init() override;
  void draw() override;

public:
  Triangle(int width, int height, std::string title);
  ~Triangle();
};
