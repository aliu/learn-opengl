#include "util/gl.h"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

GLuint VAO, VBO, program;

GLfloat vertices[] = {
  -0.5f, 0.5f, 0.0f,
  -0.5f, -0.5f, 0.0f,
  0.5f, -0.5f, 0.0f
};

void init() {
  glGenVertexArrays(1, &VAO);
  glGenBuffers(1, &VBO);

  glBindVertexArray(VAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  program = gl::shader({"triangle.vert", "triangle.frag"});
}

void loop(GLFWwindow *handle) {
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);

  glUseProgram(program);
  glBindVertexArray(VAO);

  glDrawArrays(GL_TRIANGLES, 0, 3);
}

void cleanup() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteProgram(program);
}

int main() {
  gl::Window window("Triangle", 500, 500);

  init();
  while (window) {
    loop(window.handle);
    glfwSwapBuffers(window.handle);
    glfwPollEvents();
  }
  cleanup();
}
