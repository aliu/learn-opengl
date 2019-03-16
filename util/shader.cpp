#include "shader.h"

#include <glad/glad.h>
#include <sstream>
#include <string>

GLuint compile_shader(const char *source, GLenum type) {
  GLint success;
  GLchar info_log[512];

  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &source, NULL);
  glCompileShader(shader);
  glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, info_log);
    std::stringstream msg;
    msg << "Failed to compile shader:\n" << info_log;
    throw std::runtime_error(msg.str());
  }

  return shader;
}

void Shader::compile(const char *vertex_shader, const char *fragment_shader) {
  GLuint vs = compile_shader(vertex_shader, GL_VERTEX_SHADER);
  GLuint fs = compile_shader(fragment_shader, GL_FRAGMENT_SHADER);

  GLint success;
  GLchar info_log[512];

  program = glCreateProgram();
  glAttachShader(program, vs);
  glAttachShader(program, fs);
  glLinkProgram(program);
  glGetProgramiv(program, GL_LINK_STATUS, &success);

  if (!success) {
    glGetProgramInfoLog(program, 512, NULL, info_log);
    std::stringstream msg;
    msg << "Failed to link program:\n" << info_log;
    throw std::runtime_error(msg.str());
  }

  glDeleteShader(vs);
  glDeleteShader(fs);
}

void Shader::use() { glUseProgram(program); }
