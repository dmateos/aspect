#ifndef _MODEL_H_
#define _MODEL_H_

#include "main.h"
#include "mesh.h"
#include "gl_program.h"

namespace aspect {
  class ModelAsset {
    public:
      ModelAsset(aspect::Mesh *mesh, aspect::GLProgram *program);

    private:
      aspect::Mesh *mesh;
      aspect::GLProgram *program;
      GLuint vbo, vao;
  };

  class ModelInstance {
    public:
      ModelInstance(aspect::ModelAsset *asset);
      void render();

    private:
      glm::mat4 translation;
  };
}
#endif

