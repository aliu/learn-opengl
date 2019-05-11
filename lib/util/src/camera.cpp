#include "util/gl.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

const glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f);

glm::vec3 orientation(double pitch, double yaw) {
  return glm::normalize(
      glm::vec3(glm::cos(glm::radians(pitch)) * glm::cos(glm::radians(yaw)),
                glm::sin(glm::radians(pitch)),
                glm::cos(glm::radians(pitch)) * glm::sin(glm::radians(yaw))));
}

glm::mat4 gl::Camera::view() {
  return glm::lookAt(position, position + orientation(pitch, yaw), up);
}

void gl::Camera::move(glm::vec3 direction) {
  glm::vec3 right = glm::normalize(glm::cross(orientation(pitch, yaw), up));
  glm::vec3 front = glm::normalize(glm::cross(up, right));
  position += direction.x * right;
  position += direction.z * front;
  position += direction.y * up;
}

void gl::Camera::orient(glm::vec3 front) {
  front = glm::normalize(front);
  pitch = glm::degrees(glm::asin(front.y));
  yaw = glm::degrees(glm::atan(front.z, front.x));
}
