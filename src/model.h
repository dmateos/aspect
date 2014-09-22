#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "mesh.h"
#include "gl_program.h"

namespace aspect {
  class ModelAsset {
    public:
      aspect::GLProgram *program;
      aspect::Mesh *mesh;
      GLuint vbo[2], vao, m_veo;
      ModelAsset(Mesh *mesh, GLProgram *program);
  };

  class ModelInstance {

    public:
      ModelAsset *asset;

      ModelInstance(ModelAsset *asset);
      void set_position(const glm::vec3 &position);
      void offset_position(const glm::vec3 &position);
      glm::vec3 get_position() const;
      void scale(float n);

      glm::mat4 orientation() const;
      void offset_orientation(float up, float right);

      glm::vec3 forward() const;
      glm::vec3 right() const;
      glm::vec3 up() const;

      void update();
      glm::mat4 matrix() const;

      void normalize();

      void draw(glm::mat4 camera);

    private:
      glm::mat4 m_matrix;
      glm::vec3 m_position;
      float m_horizontalangle;
      float m_verticalangle;
  };
}
#endif

