#include "util/gl.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

#include <glad/glad.h>
#include <iostream>
#include <string>

GLuint gl::texture2D(const std::string &filename) {
  GLuint texture;
  std::string path = "assets/textures/" + filename;

  glGenTextures(1, &texture);
  glBindTexture(GL_TEXTURE_2D, texture);

  stbi_set_flip_vertically_on_load(true);

  int width, height, channels;
  unsigned char *data = stbi_load(path.c_str(), &width, &height, &channels, 0);

  if (data) {
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
    glGenerateMipmap(GL_TEXTURE_2D);
  } else {
    std::cerr << "Failed to load texture: " << filename << '\n';
  }

  stbi_image_free(data);

  return texture;
}
