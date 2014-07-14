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
      GLuint vbo, vao;

      ModelAsset(aspect::Mesh *mesh, aspect::GLProgram *program);

    private:
  };

  class ModelInstance {
    public:
      aspect::ModelAsset *asset;
      glm::mat4 transform;

      ModelInstance(aspect::ModelAsset *asset);

    private:
  };
}
#endif

