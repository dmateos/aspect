#ifndef _CUBE_H_
#define _CUBE_H_

#include "main.h"
#include "gl_program.h"
#include <vector>

#define CCOUNT 16
#define CSIZE 2.0f

namespace aspect {
  class CubeChunk {
    public:
      CubeChunk(GLProgram *program);
      ~CubeChunk();
      void update();
      void draw(glm::mat4 camera);
    private:
      int m_cube[CCOUNT][CCOUNT][CCOUNT];
      std::vector<float> m_verticies;
      GLuint m_vbo, m_vao;
      GLProgram *program;
  };
}

#endif

