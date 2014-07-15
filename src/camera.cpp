#include "camera.h"

using namespace aspect; 

Camera::Camera() {
  m_view = glm::mat4(1.0f);
  m_orientation = glm::mat4(1.0f);
  m_perspective = glm::perspective(45.0f, 4.0f/3.0f, 0.1f, 1000.0f);
}

glm::mat4 Camera::matrix() {
  return m_perspective * m_orientation * m_view;
}

void Camera::translate(const glm::vec3& vec) {
  m_view = glm::translate(m_view, vec);
}

void Camera::rotate(const glm::vec3 &vec, float step) {
  m_orientation = glm::rotate(m_orientation, step, vec);
}
