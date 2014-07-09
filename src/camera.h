#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "main.h"

namespace aspect {
  class Camera {
    public:
      Camera();

      glm::mat4 matrix();
      glm::mat4 perspective();
      glm::mat4 view();

      void pitch(float n);
      void yaw(float n);
      void position_x(float n);
      void position_y(float n);

    private:
      glm::vec3 position;
      glm::vec3 target;
      glm::vec3 up;
  };
}

#endif
