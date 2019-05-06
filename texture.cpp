#include "util/gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint VAO, VBO, EBO, texture, program;

GLfloat vertices[] = {
  // position         // texture
  -0.5f, 0.5f, 0.0f,  0.0f, 1.0f,
  -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
  0.5f, -0.5f, 0.0f,  1.0f, 0.0f,
  0.5f, 0.5f, 0.0f,   1.0f, 1.0f
};

GLuint indices[] = {
  0, 1, 2,
  0, 2, 3
};

void init() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  texture = gl::texture2D("diamond_ore.png");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  program = gl::shader({"texture.vert", "texture.frag"});
  glUseProgram(program);
  glUniform1i(glGetUniformLocation(program, "diamond"), 0);
}

void loop(GLFWwindow *handle) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glUseProgram(program);
  glBindVertexArray(VAO);

  glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, (void*)0);
}

void cleanup() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteTextures(1, &texture);
  glDeleteProgram(program);
}

int main() {
  gl::Window window("Texture", 500, 500);

  init();
  while (window) {
    loop(window.handle);
    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }
  cleanup();
}
