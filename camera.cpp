#include "util/gl.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VAO, VBO, EBO, texture, program;

GLfloat vertices[] = {
  // position           // texture
  0.5f, -0.5f, 0.5f,    0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
  0.5f, 0.5f, 0.5f,     0.0f, 1.0f,
  0.5f, 0.5f, -0.5f,    1.0f, 1.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  -0.5f, -0.5f, 0.5f,   1.0f, 0.0f,
  -0.5f, 0.5f, -0.5f,   0.0f, 1.0f,
  -0.5f, 0.5f, 0.5f,    1.0f, 1.0f,

  -0.5f, 0.5f, 0.5f,    0.0f, 0.0f,
  0.5f, 0.5f, 0.5f,     1.0f, 0.0f,
  -0.5f, 0.5f, -0.5f,   0.0f, 1.0f,
  0.5f, 0.5f, -0.5f,    1.0f, 1.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,   1.0f, 0.0f,
  -0.5f, -0.5f, 0.5f,   0.0f, 1.0f,
  0.5f, -0.5f, 0.5f,    1.0f, 1.0f,

  -0.5f, -0.5f, 0.5f,   0.0f, 0.0f,
  0.5f, -0.5f, 0.5f,    1.0f, 0.0f,
  -0.5f, 0.5f, 0.5f,    0.0f, 1.0f,
  0.5f, 0.5f, 0.5f,     1.0f, 1.0f,

  0.5f, -0.5f, -0.5f,   0.0f, 0.0f,
  -0.5f, -0.5f, -0.5f,  1.0f, 0.0f,
  0.5f, 0.5f, -0.5f,    0.0f, 1.0f,
  -0.5f, 0.5f, -0.5f,   1.0f, 1.0f
};

GLuint indices[] = {
  0, 1, 2, 1, 2, 3,
  4, 5, 6, 5, 6, 7,
  8, 9, 10, 9, 10, 11,
  12, 13, 14, 13, 14, 15,
  16, 17, 18, 17, 18, 19,
  20, 21, 22, 21, 22, 23
};

void init() {
  glEnable(GL_DEPTH_TEST);

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

  program = gl::shader({"cube.vert", "texture.frag"});
  glUseProgram(program);
  glUniform1i(glGetUniformLocation(program, "diamond"), 0);
}

void draw(glm::mat4 transform) {
  glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture);

  glUseProgram(program);
  glBindVertexArray(VAO);

  glUniformMatrix4fv(glGetUniformLocation(program, "transform"), 1, GL_FALSE, glm::value_ptr(transform));
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}

void cleanup() {
  glDeleteVertexArrays(1, &VAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteTextures(1, &texture);
  glDeleteProgram(program);
}

int main() {
  gl::Window window("Camera", 500, 500);
  window.setCamera(glm::vec3(0.0f, 2.0f, 0.0f), glm::vec3(0.0f, 0.0f, -1.0f));

  init();
  while (window) {
    window.update();

    auto screen = window.getSize();
    float ratio = (float)screen.first / (float)screen.second;

    glm::mat4 model = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -8.0f));
    glm::mat4 view = window.getView();
    glm::mat4 projection = glm::perspective(0.25f * glm::pi<float>(), ratio, 0.1f, 100.0f);
    glm::mat4 transform = projection * view * model;

    draw(transform);
    window.render();
  }
  cleanup();
}
