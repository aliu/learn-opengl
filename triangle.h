#pragma once

class Triangle {
  unsigned int shader_program;
  unsigned int VAO, VBO;
 public:
  Triangle();
  ~Triangle();
  void draw();
};
