#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

namespace aspect {
  class Camera {
    public:
      Camera();

      glm::mat4 matrix();
      void translate(const glm::vec3 &vec);
      void rotate(const glm::vec3 &vec);

    private:
      glm::vec3 m_position;
      glm::mat4 m_view;
      glm::mat4 m_orientation;
      glm::mat4 m_perspective;
  };
}

#endif
