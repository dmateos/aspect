#ifndef _CUBE_H_
#define _CUBE_H_

#include "main.h"
#include "gl_program.h"
#include <vector>

#define CSIZE 10
namespace aspect {
  class CubeChunk {
    public:
      CubeChunk(GLProgram *program);
      void update();
      void draw(glm::mat4 camera);
    private:
      int m_cube[CSIZE][CSIZE][CSIZE];
      std::vector<float> m_verticies;
      GLuint m_vbo, m_vao;
      GLProgram *program;
  };
}

#endif

