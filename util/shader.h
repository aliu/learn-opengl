#pragma once

#include <glad/glad.h>
#include <string>

class Shader {
  GLuint program;

public:
  void compile(const char *vertex_shader, const char *fragment_shader);
  void use();
};
