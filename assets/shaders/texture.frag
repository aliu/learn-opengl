#version 330 core
out vec4 color;

in vec2 tex;

uniform sampler2D diamond;

void main() {
  color = texture(diamond, tex);
}
