#include "util/gl.h"

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

glm::vec3 lightColor = glm::vec3(1.0f);
glm::vec3 cubeColor = glm::vec3(0.2f, 0.5f, 0.8f);

GLuint lightVAO, cubeVAO;
GLuint VBO, EBO;
GLuint lightShader, phongShader;

GLfloat vertices[] = {
  // position           // normal
  0.5f, -0.5f, 0.5f,    1.0f, 0.0f, 0.0f,
  0.5f, -0.5f, -0.5f,   1.0f, 0.0f, 0.0f,
  0.5f, 0.5f, 0.5f,     1.0f, 0.0f, 0.0f,
  0.5f, 0.5f, -0.5f,    1.0f, 0.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  -1.0f, 0.0f, 0.0f,
  -0.5f, -0.5f, 0.5f,   -1.0f, 0.0f, 0.0f,
  -0.5f, 0.5f, -0.5f,   -1.0f, 0.0f, 0.0f,
  -0.5f, 0.5f, 0.5f,    -1.0f, 0.0f, 0.0f,

  -0.5f, 0.5f, 0.5f,    0.0f, 1.0f, 0.0f,
  0.5f, 0.5f, 0.5f,     0.0f, 1.0f, 0.0f,
  -0.5f, 0.5f, -0.5f,   0.0f, 1.0f, 0.0f,
  0.5f, 0.5f, -0.5f,    0.0f, 1.0f, 0.0f,

  -0.5f, -0.5f, -0.5f,  0.0f, -1.0f, 0.0f,
  0.5f, -0.5f, -0.5f,   0.0f, -1.0f, 0.0f,
  -0.5f, -0.5f, 0.5f,   0.0f, -1.0f, 0.0f,
  0.5f, -0.5f, 0.5f,    0.0f, -1.0f, 0.0f,

  -0.5f, -0.5f, 0.5f,   0.0f, 0.0f, 1.0f,
  0.5f, -0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
  -0.5f, 0.5f, 0.5f,    0.0f, 0.0f, 1.0f,
  0.5f, 0.5f, 0.5f,     0.0f, 0.0f, 1.0f,

  0.5f, -0.5f, -0.5f,   0.0f, 0.0f, -1.0f,
  -0.5f, -0.5f, -0.5f,  0.0f, 0.0f, -1.0f,
  0.5f, 0.5f, -0.5f,    0.0f, 0.0f, -1.0f,
  -0.5f, 0.5f, -0.5f,   0.0f, 0.0f, -1.0f
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

  glGenVertexArrays(1, &lightVAO);
  glGenVertexArrays(1, &cubeVAO);
  glGenBuffers(1, &VBO);
  glGenBuffers(1, &EBO);

  glBindVertexArray(lightVAO);

  glBindBuffer(GL_ARRAY_BUFFER, VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glBindVertexArray(cubeVAO);

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)0);
  glEnableVertexAttribArray(0);

  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(GLfloat), (void*)(3 * sizeof(GLfloat)));
  glEnableVertexAttribArray(1);

  lightShader = gl::shader({"light.vert", "light.frag"});

  phongShader = gl::shader({"phong.vert", "phong.frag"});
  glUseProgram(phongShader);
  gl::setUniform(phongShader, "light_color", lightColor);
  gl::setUniform(phongShader, "object_color", cubeColor);
}

void draw() {
  glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

  glUseProgram(lightShader);
  glBindVertexArray(lightVAO);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);

  glUseProgram(phongShader);
  glBindVertexArray(cubeVAO);
  glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, (void*)0);
}

void cleanup() {
  glDeleteVertexArrays(1, &lightVAO);
  glDeleteVertexArrays(1, &cubeVAO);
  glDeleteBuffers(1, &VBO);
  glDeleteBuffers(1, &EBO);
  glDeleteProgram(lightShader);
  glDeleteProgram(phongShader);
}

int main() {
  gl::Window window("Phong Lighting", 500, 500);
  window.setCamera(glm::vec3(2.0f, 1.0f, 3.0f), glm::vec3(-2.0f, -1.0f, -3.0f));
  double rotation = 0;

  init();
  while (window) {
    double delta = window.update();
    rotation += delta;

    auto screen = window.getSize();
    float ratio = (float)screen.first / (float)screen.second;

    glm::mat4 view = window.getView();
    glm::mat4 projection = glm::perspective(0.25f * glm::pi<float>(), ratio, 0.1f, 100.0f);

    glm::vec3 lightPosition = glm::vec3(2.0f * glm::sin(rotation), 1.0f, 2.0f * glm::cos(rotation));
    glm::mat4 lightModel = glm::mat4(1.0f);
    lightModel = glm::translate(lightModel, lightPosition);
    lightModel = glm::scale(lightModel, glm::vec3(0.25f));

    glUseProgram(lightShader);
    gl::setUniform(lightShader, "model", lightModel);
    gl::setUniform(lightShader, "view", view);
    gl::setUniform(lightShader, "projection", projection);

    glUseProgram(phongShader);
    gl::setUniform(phongShader, "model", glm::mat4(1.0f));
    gl::setUniform(phongShader, "view", view);
    gl::setUniform(phongShader, "projection", projection);
    gl::setUniform(phongShader, "view_pos", window.getPosition());
    gl::setUniform(phongShader, "light_pos", lightPosition);

    draw();
    window.render();
  }
  cleanup();
}
