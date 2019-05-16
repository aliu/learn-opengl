#version 330 core

layout(location = 0) in vec3 in_pos;
layout(location = 1) in vec3 in_normal;
layout(location = 2) in vec2 in_tex;

out VertexData {
  vec3 pos;
  vec3 normal;
  vec2 tex;
} data;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
  gl_Position = projection * view * model * vec4(in_pos, 1.0);
  data.pos = vec3(model * vec4(in_pos, 1.0));
  data.normal = mat3(transpose(inverse(model))) * in_normal;
  data.tex = in_tex;
}
