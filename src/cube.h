#ifndef _CUBE_H_
#define _CUBE_H_

#include "main.h"
#include "gl_program.h"
#include <vector>

#define CCOUNTX 16   //cubes horizontally
#define CCOUNTY 16     //vertically
#define CCOUNTZ 16   //inward
#define CSIZE 1.0f    //size of cubes
#define CSEP 0.0f     //seperation between cubes

namespace aspect {
  class CubeChunk {
    public:
      CubeChunk(GLProgram *program);
      ~CubeChunk();
      void update();
      void draw(glm::mat4 camera) const;
    private:
      int m_cube[CCOUNTX][CCOUNTY][CCOUNTZ];
      std::vector<float> m_verticies;
      GLuint m_vbo, m_vao;
      GLProgram *program;
  };
}

#endif

