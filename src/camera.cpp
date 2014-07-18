#include "camera.h"

using namespace aspect;

static const float maxvert = 85.0f; //gimbal lock :(

static inline float radtodeg(float rad) {
  return rad * 180.0f / 3.14159265359;
}

Camera::Camera() :
  m_position(0.0f, 0.0f, 1.0f),
  m_horizontalangle(0.0f),
  m_verticalangle(0.0f),
  m_fov(45.0f),
  m_nearplane(0.01f),
  m_farplane(1000.0f),
  m_aspect((float)XRES/(float)YRES)
{

}

glm::vec3& Camera::position() {
  return m_position;
}

void Camera::set_position(const glm::vec3 &position) {
  m_position = position;
}

void Camera::offset_position(const glm::vec3 &position) {
  m_position += position;
}

glm::mat4 Camera::orientation() const {
  glm::mat4 orientation;
  orientation = glm::rotate(orientation, m_verticalangle, glm::vec3(1,0,0));
  orientation = glm::rotate(orientation, m_horizontalangle, glm::vec3(0,1,0));
  return orientation;
}

void Camera::offset_orientation(float up, float right) {
  m_horizontalangle += right;
  m_verticalangle += up;
  normalize();
}

glm::vec3 Camera::forward() const {
  glm::vec4 forward = glm::inverse(orientation()) * glm::vec4(0,0,-1,1);
  return glm::vec3(forward);
}

glm::vec3 Camera::right() const {
  glm::vec4 right = glm::inverse(orientation()) * glm::vec4(1,0,0,1);
  return glm::vec3(right);
}

glm::vec3 Camera::up() const {
  glm::vec4 up = glm::inverse(orientation()) * glm::vec4(0,1,0,1);
  return glm::vec3(up);
}

glm::mat4 Camera::matrix() const {
  return glm::perspective(m_fov, m_aspect, m_nearplane, m_farplane) *
          orientation() * glm::translate(glm::mat4(), -m_position);
}

void Camera::normalize() {
  m_horizontalangle = fmodf(m_horizontalangle, 360.0f);
  if(m_horizontalangle < 0.0f)
    m_horizontalangle += 360.0f;

  if(m_verticalangle > maxvert)
    m_verticalangle = maxvert;
  else if(m_verticalangle < - maxvert)
    m_verticalangle = -maxvert;
}
