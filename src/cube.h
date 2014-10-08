#ifndef _CUBE_H_
#define _CUBE_H_

#include "main.h"
#include "gl_program.h"
#include "texture.h"
#include <vector>

#define CCOUNTX 16   //wide
#define CCOUNTY 16  //deep
#define CCOUNTZ 16   //long
#define CSIZE 1.0f    //size of cubes
#define CSEP 0.0f     //seperation between cubes

namespace aspect {
  class CubeChunk {
    public:
      CubeChunk(GLProgram *program, float xoffset, float yoffset, float zoffset);
      ~CubeChunk();
      void update();
      void draw(glm::mat4 camera) const;
      float xoffset, yoffset, zoffset;
    private:
      int m_cube[CCOUNTX][CCOUNTY][CCOUNTZ];
      TextureAtlas *texture;
      GLuint m_vbo, m_vao, m_veo, veolen;
      GLProgram *program;
      glm::mat4 translate;
  };
}

#endif

