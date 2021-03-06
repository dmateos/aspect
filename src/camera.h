#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

namespace aspect {
  class Camera {
    public:
      Camera();
      glm::vec3& position();
      void set_position(const glm::vec3 &position);
      void offset_position(const glm::vec3 &position);
      glm::vec3 get_position() const;

      glm::mat4 orientation() const;
      void offset_orientation(float up, float right);

      glm::vec3 forward(float step) const;
      glm::vec3 right(float step) const;
      glm::vec3 up(float step) const;

      glm::mat4 matrix() const;

      void normalize();

    private:
      glm::vec3 m_position;
      float m_horizontalangle;
      float m_verticalangle;

      float m_fov;
      float m_nearplane;
      float m_farplane;
      float m_aspect;
  };
}

#endif
