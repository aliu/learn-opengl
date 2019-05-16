#include "util/gl.h"
#include "fs.h"

#include <glad/glad.h>
#include <glm/vec3.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <fstream>
#include <initializer_list>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

const GLsizei LOG_SIZE = 1024;
GLchar infoLog[LOG_SIZE];

std::string read(const std::string &filename) {
  std::ifstream file(fs::getPath("assets/shaders/" + filename));
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
    std::cerr << "Failed to compile shader: " << filename << '\n' << infoLog;
  }

  return shader;
}

GLuint gl::shader(std::initializer_list<std::string> filenames) {
  GLuint program = glCreateProgram();
  std::vector<GLuint> shaders;

  for (auto &filename : filenames) {
    GLuint shader = compile(filename);
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

void gl::setUniform(GLuint program, const std::string &name, GLint value) {
  glUniform1i(glGetUniformLocation(program, name.c_str()), value);
}

void gl::setUniform(GLuint program, const std::string &name, glm::vec3 value) {
  glUniform3f(glGetUniformLocation(program, name.c_str()), value.x, value.y, value.z);
}

void gl::setUniform(GLuint program, const std::string &name, glm::mat4 value) {
  glUniformMatrix4fv(glGetUniformLocation(program, name.c_str()), 1, GL_FALSE, glm::value_ptr(value));
}
