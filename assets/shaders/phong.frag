#version 330 core

in vec3 normal;
in vec3 pos;

out vec4 color;

uniform vec3 view_pos;
uniform vec3 light_color;
uniform vec3 light_pos;
uniform vec3 object_color;

void main() {
  vec3 ambient = 0.1 * light_color;

  vec3 norm = normalize(normal);
  vec3 light_direction = normalize(light_pos - pos);
  vec3 diffuse = max(dot(norm, light_direction), 0.0) * light_color;

  vec3 view_direction = normalize(view_pos - pos);
  vec3 reflect_direction = reflect(-light_direction, norm);

  float spec = 0.5 * pow(max(dot(view_direction, reflect_direction), 0.0), 32);
  vec3 specular = spec * light_color;

  color = vec4((ambient + diffuse + specular) * object_color, 1.0);
}
