#include "cube.h"

#include <string>
#include <string.h>
#include <iostream>

using namespace aspect;

CubeChunk::CubeChunk(GLProgram *program) : program(program){
  for(int x = 0; x < CCOUNTX; x++) {
    for(int y = 0; y < CCOUNTY; y++) {
      for(int z = 0; z < CCOUNTZ; z++) {
        m_cube[x][y][z] = 1;
      }
    }
  }

  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);
  glGenBuffers(1, &m_vbo);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_verticies.size() * 3 * sizeof(float),
               &m_verticies[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(program->get_attrib("vp"));
  glVertexAttribPointer(program->get_attrib("vp"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

CubeChunk::~CubeChunk() {

}

#define push_three(v, x,y,z)  v.push_back(x); v.push_back(y); v.push_back(z);

void CubeChunk::update() {
  for(int xp = 0, x = 0; xp < CCOUNTX; xp += 1, x += CSIZE+1) {
    for(int yp = 0, y = 0; yp < CCOUNTY; yp += 1, y += CSIZE+1) {
      for(int zp = 0, z = 0; zp < CCOUNTZ; zp +=1, z += CSIZE+1) {
        if(m_cube[xp][yp][zp] == 1) {
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+CSIZE);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+0.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+0.0f);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(m_verticies, x+0.0f,y+0.0f,z+0.0f);
          push_three(m_verticies, x+CSIZE, y+0.0f,z+0.0f);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+0.0f);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f,y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+0.0f);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(m_verticies, x+0.0f, y+0.0f, z+CSIZE);
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+0.0f, y+0.0f, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+0.0f);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+0.0f);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+0.0f);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+0.0f);
          push_three(m_verticies, x+0.0f, y+CSIZE,z+0.0f);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+0.0f);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(m_verticies, x+CSIZE, y+0.0f, z+CSIZE);
        }
      }
    }
  }
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, m_verticies.size() * sizeof(float), &m_verticies[0], GL_STATIC_DRAW);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void CubeChunk::draw(glm::mat4 camera) {
  program->use();
  program->set_uniform("camera", camera);
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, m_verticies.size());  
  glBindVertexArray(0);
}
