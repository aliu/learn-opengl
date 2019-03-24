#include "util/gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint program, VAO, EBO, VBO, texture;

float vertices[] = {
  // position         // texture
  -0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
  0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
  0.5f, 0.5f, 0.0f,   1.0f, 1.0f
};

unsigned int indices[] = {
  0, 1, 2,
  0, 2, 3
};

void init() {
  program = gl::shader({"texture.vert", "texture.frag"});

  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &EBO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
  glEnableVertexAttribArray(1);

  texture = gl::texture2D("diamond_ore.png");

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  glUseProgram(program);
  glUniform1i(glGetUniformLocation(program, "diamond"), 0);
}

void loop(GLFWwindow *window) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glUseProgram(program);
  glBindVertexArray(VAO);
  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

void cleanup() {
  glDeleteProgram(program);
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &EBO);
  glDeleteBuffers(1, &VBO);
  glDeleteTextures(1, &texture);
}

int main() { gl::run({"Texture"}, init, loop, cleanup); }
