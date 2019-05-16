#include "util/gl.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

GLuint VAO, VBO, EBO, texture, program;

GLfloat vertices[] = {
  // position          // normal           // texture
  -0.5f, 0.0f, 0.5f,   0.0f, 1.0f, 0.0f,   0.0f, 0.0f,
  0.5f, 0.0f, 0.5f,    0.0f, 1.0f, 0.0f,   10.0f, 0.0f,
  -0.5f, 0.0f, -0.5f,  0.0f, 1.0f, 0.0f,   0.0f, 10.0f,
  0.5f, 0.0f, -0.5f,   0.0f, 1.0f, 0.0f,   10.0f, 10.0f
};

GLuint indices[] = { 0, 1, 2, 1, 2, 3 };

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

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(GLfloat), (void*)(6 * sizeof(GLfloat)));
  glEnableVertexAttribArray(2);

  texture = gl::texture2D("cobblestone.png");
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_NEAREST);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

  program = gl::shader({"blinn.vert", "blinn.frag"});
  glUseProgram(program);
  gl::setUniform(program, "surface", 0);
  gl::setUniform(program, "light_color", glm::vec3(1.0f));
  gl::setUniform(program, "light_pos", glm::vec3(0.0f));
}

void draw() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

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
  gl::Window window("Blinn-Phong Lighting", 500, 500);

  init();
  while (window) {
    window.update();

    auto screen = window.getSize();
    float ratio = (float)screen.first / (float)screen.second;

    glm::mat4 view = window.getView();
    glm::mat4 projection = glm::perspective(0.25f * glm::pi<float>(), ratio, 0.1f, 100.0f);

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, -1.0f, 0.0f));
    model = glm::scale(model, glm::vec3(10.0f));

    glUseProgram(program);
    gl::setUniform(program, "model", model);
    gl::setUniform(program, "view", view);
    gl::setUniform(program, "projection", projection);
    gl::setUniform(program, "view_pos", window.getPosition());

    draw();
    window.render();
  }
  cleanup();
}
