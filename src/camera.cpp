#include "camera.h"

aspect::Camera::Camera() :
  position(0.0f, 0.0f, 10.0f),
  target(0.0f, 0.0f, 0.0f),
  up(0.0f, 1.0f, 0.0f) 
{

}

glm::mat4 aspect::Camera::matrix() {
  return perspective() * view();
}

glm::mat4 aspect::Camera::perspective() {
  return glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 100.0f);
}

glm::mat4 aspect::Camera::view() {
  glm::mat4 view = glm::lookAt(
      glm::vec3(this->position),
      glm::vec3(this->target),
      glm::vec3(this->up) 
  );

  return view;
}

void aspect::Camera::pitch(float n) {
  position.y += n;
}

void aspect::Camera::yaw(float n) {
  position.x += n;
}

void aspect::Camera::position_x(float n) {
  target.x += n;
}

void aspect::Camera::position_y(float n) {
  target.y += n;
}
