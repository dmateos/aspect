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
      GLuint vbo[2], vao;

      ModelAsset(Mesh *mesh, GLProgram *program);
    private:
  };

  class ModelInstance {
    public:
      ModelAsset *asset;
      glm::mat4 transform;

      ModelInstance(ModelAsset *asset);
      glm::mat4 matrix();
      void translate(const glm::vec3 &vec);
      void rotate(const glm::vec3 &vec);
    private:
  };
}
#endif

