#include "cube.h"

#include <string>
#include <string.h>
#include <iostream>

using namespace aspect;

CubeChunk::CubeChunk(GLProgram *program, float xoffset, float yoffset, float zoffset) :
  program(program), xoffset(xoffset), yoffset(yoffset), zoffset(zoffset) {
  for(int x = 0; x < CCOUNTX; x++) {
    for(int y = 0; y < CCOUNTY; y++) {
      for(int z = 0; z < CCOUNTZ; z++) {
        m_cube[x][y][z] = 1;
      }
    }
  }

  translate = glm::translate(glm::mat4(), glm::vec3(xoffset, yoffset, zoffset));
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);
  glGenBuffers(1, &m_vbo);

  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glEnableVertexAttribArray(program->get_attrib("vp"));
  glVertexAttribPointer(program->get_attrib("vp"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  printf("new cube chunk %dx%dx%d with size %g and sep %g\n", CCOUNTX, CCOUNTY, CCOUNTX, CSIZE, CSEP);
}

CubeChunk::~CubeChunk() {

}

#define push_three(v, x,y,z)  v.push_back(x); v.push_back(y); v.push_back(z);

void CubeChunk::update() {
  std::vector<float> verticies;
  for(int xp = 0, x = 0; xp < CCOUNTX; xp += 1, x += CSIZE+CSEP) {
    for(int yp = 0, y = 0; yp < CCOUNTY; yp += 1, y += CSIZE+CSEP) {
      for(int zp = 0, z = 0; zp < CCOUNTZ; zp +=1, z += CSIZE+CSEP) {
        if(m_cube[xp][yp][zp] == 1) {
          //first
          push_three(verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(verticies, x+0.0f, y+0.0f, z+CSIZE);
          push_three(verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(verticies, x+CSIZE, y+CSIZE, z+0.0f);
          push_three(verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(verticies, x+0.0f, y+CSIZE, z+0.0f);
          //second
          push_three(verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(verticies, x+0.0f,y+0.0f,z+0.0f);
          push_three(verticies, x+CSIZE, y+0.0f,z+0.0f);
          push_three(verticies, x+CSIZE, y+CSIZE, z+0.0f);
          push_three(verticies, x+CSIZE, y+0.0f, z+0.0f);
          push_three(verticies, x+0.0f,y+0.0f, z+0.0f);
          //third
          push_three(verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(verticies, x+0.0f, y+CSIZE, z+0.0f);
          push_three(verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(verticies, x+0.0f, y+0.0f, z+CSIZE);
          push_three(verticies, x+0.0f, y+0.0f, z+0.0f);
          //forth
          push_three(verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(verticies, x+0.0f, y+0.0f, z+CSIZE);
          push_three(verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(verticies, x+CSIZE, y+0.0f, z+0.0f);
          push_three(verticies, x+CSIZE, y+CSIZE, z+0.0f);
          //fith
          push_three(verticies, x+CSIZE, y+0.0f, z+0.0f);
          push_three(verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(verticies, x+CSIZE, y+0.0f, z+CSIZE);
          push_three(verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(verticies, x+CSIZE, y+CSIZE, z+0.0f);
          push_three(verticies, x+0.0f, y+CSIZE,z+0.0f);
          //six
          push_three(verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(verticies, x+0.0f, y+CSIZE, z+0.0f);
          push_three(verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(verticies, x+CSIZE, y+CSIZE, z+CSIZE);
          push_three(verticies, x+0.0f, y+CSIZE, z+CSIZE);
          push_three(verticies, x+CSIZE, y+0.0f, z+CSIZE);
        }
      }
    }
  }
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  //TODO is static draw the best? also is there a more dedicated function to do this?
  glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies[0], GL_STATIC_DRAW);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  vbolen = verticies.size();

  printf("updated chunk with %d cubes with %zu verticies(%zu bytes)\n", CCOUNTX*CCOUNTY*CCOUNTZ, verticies.size(),
          verticies.size()*sizeof(float));
}

void CubeChunk::draw(glm::mat4 camera) const {
  program->use();
  program->set_uniform("camera", camera);
  program->set_uniform("translate", translate);
  glBindVertexArray(m_vao);
  glDrawArrays(GL_TRIANGLES, 0, vbolen);
  glBindVertexArray(0);
}
