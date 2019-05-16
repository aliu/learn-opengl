#version 330 core

in VertexData {
  vec3 pos;
  vec3 normal;
  vec2 tex;
} data;

out vec4 color;

uniform sampler2D surface;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 view_pos;

void main() {
  vec3 ambient = 0.1 * light_color;

  vec3 norm = normalize(data.normal);
  vec3 light_direction = normalize(light_pos - data.pos);
  vec3 diffuse = max(dot(norm, light_direction), 0.0) * light_color;

  vec3 view_direction = normalize(view_pos - data.pos);
  vec3 blinn = normalize(light_direction + view_direction);

  float spec = 0.5 * pow(max(dot(norm, blinn), 0.0), 4.0);
  vec3 specular = spec * light_color;

  vec3 tex = texture(surface, data.tex).rgb;
  color = vec4((ambient + diffuse + specular) * tex, 1.0);
}
