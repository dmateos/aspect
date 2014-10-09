#include "cube.h"

#include <string>
#include <string.h>
#include <iostream>

using namespace aspect;

CubeChunk::CubeChunk(GLProgram *program, float xoffset, float yoffset, float zoffset) :
  xoffset(xoffset), yoffset(yoffset), zoffset(zoffset), program(program) {
  for(int x = 0; x < CCOUNTX; x++) {
    for(int y = 0; y < CCOUNTY; y++) {
      for(int z = 0; z < CCOUNTZ; z++) {
        m_cube[x][y][z] = rand() % 3;
      }
    }
  }

  translate = glm::translate(glm::mat4(), glm::vec3(xoffset, yoffset, zoffset));
  glGenVertexArrays(1, &m_vao);
  glBindVertexArray(m_vao);
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glGenBuffers(1, &m_veo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo);

  glEnableVertexAttribArray(program->get_attrib("vp"));
  glVertexAttribPointer(program->get_attrib("vp"), 3, GL_FLOAT, GL_FALSE, 5*sizeof(float), NULL);

  glEnableVertexAttribArray(program->get_attrib("tex"));
  glVertexAttribPointer(program->get_attrib("tex"), 2, GL_FLOAT, GL_FALSE, 5*sizeof(float), 
      (void*)(3*sizeof(float)));

  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  texture = new TextureAtlas("textures/atlastest2.png");
  texture->bind_texture();
  printf("new cube chunk %dx%dx%d with size %g and sep %g\n", CCOUNTX, CCOUNTY, CCOUNTX, CSIZE, CSEP);
}

CubeChunk::~CubeChunk() {
  delete texture;
}

#define push_three(v, x,y,z)  v.push_back(x); v.push_back(y), v.push_back(z);
#define push_five(v, x,y,z,w,h)  v.push_back(x); v.push_back(y); v.push_back(z), v.push_back(w); v.push_back(h);

void CubeChunk::update() {
  std::vector<float> verticies;
  std::vector<unsigned short> index;
  int vcount = 24;
  int it = 0;
  for(int xp = 0, x = 0; xp < CCOUNTX; xp += 1, x += CSIZE+CSEP) {
    for(int yp = 0, y = 0; yp < CCOUNTY; yp += 1, y += CSIZE+CSEP) {
      for(int zp = 0, z = 0; zp < CCOUNTZ; zp +=1, z += CSIZE+CSEP) {
        if(m_cube[xp][yp][zp]) {
          glm::vec4 tc;
          if(m_cube[xp][yp][zp] == 1) {
            tc = texture->get_tile(32, 32, 0, 3);
          } else if(m_cube[xp][yp][zp] == 2) {
            tc = texture->get_tile(32, 32, 2, 9);
          }
          //front
          push_five(verticies, x+0.0f, y+0.0f, z+CSIZE, tc[0], tc[1]);
          push_five(verticies, x+CSIZE, y+0.0f, z+CSIZE, tc[2], tc[1]);
          push_five(verticies, x+CSIZE, y+CSIZE, z+CSIZE, tc[2], tc[3]);
          push_five(verticies, x+0.0f, y+CSIZE, z+CSIZE, tc[0], tc[3]);
          push_three(index, it*vcount+0, it*vcount+1, it*vcount+2);
          push_three(index, it*vcount+2, it*vcount+3, it*vcount+0);
          //top
          push_five(verticies, x+0.0f, y+CSIZE, z+CSIZE, tc[0], tc[1]);
          push_five(verticies, x+CSIZE, y+CSIZE, z+CSIZE, tc[2], tc[1]);
          push_five(verticies, x+CSIZE, y+CSIZE, z+0.0f, tc[2], tc[3]);
          push_five(verticies, x+0.0f, y+CSIZE, z+0.0f,  tc[0], tc[3]);
          push_three(index, it*vcount+4, it*vcount+5, it*vcount+6);
          push_three(index, it*vcount+6, it*vcount+7, it*vcount+4);
          //back
          push_five(verticies, x+CSIZE, y+0.0f, z+0.0f, tc[0], tc[1]);
          push_five(verticies, x+0.0f, y+0.0f, z+0.0f, tc[2], tc[1]);
          push_five(verticies, x+0.0f, y+CSIZE, z+0.0f, tc[2], tc[3]);
          push_five(verticies, x+CSIZE, y+CSIZE, z+0.0f, tc[0], tc[3]);
          push_three(index, it*vcount+8, it*vcount+9, it*vcount+10);
          push_three(index, it*vcount+10, it*vcount+11, it*vcount+8);
          //bottom
          push_five(verticies, x+0.0f, y+0.0f, z+0.0f, tc[0], tc[1]);
          push_five(verticies, x+CSIZE, y+0.0f, z+0.0f, tc[2], tc[1]);
          push_five(verticies, x+CSIZE, y+0.0f, z+CSIZE, tc[2], tc[3]);
          push_five(verticies, x+0.0f, y+0.0f, z+CSIZE, tc[0], tc[3]);
          push_three(index, it*vcount+12, it*vcount+13, it*vcount+14);
          push_three(index, it*vcount+14, it*vcount+15, it*vcount+12);
          //left
          push_five(verticies, x+0.0f, y+0.0f, z+0.0f, tc[0], tc[1]);
          push_five(verticies, x+0.0f, y+0.0f, z+CSIZE, tc[2], tc[1]);
          push_five(verticies, x+0.0f, y+CSIZE, z+CSIZE, tc[2], tc[3]);
          push_five(verticies, x+0.0f, y+CSIZE, z+0.0f, tc[0], tc[3]);
          push_three(index, it*vcount+16, it*vcount+17, it*vcount+18);
          push_three(index, it*vcount+18, it*vcount+19, it*vcount+16);
          //right
          push_five(verticies, x+CSIZE, y+0.0f, z+CSIZE, tc[0], tc[1]);
          push_five(verticies, x+CSIZE, y+0.0f, z+0.0f, tc[2], tc[1]);
          push_five(verticies, x+CSIZE, y+CSIZE, z+0.0f, tc[2], tc[3]);
          push_five(verticies, x+CSIZE, y+CSIZE, z+CSIZE, tc[0], tc[3]);
          push_three(index, it*vcount+20, it*vcount+21, it*vcount+22);
          push_three(index, it*vcount+22, it*vcount+23, it*vcount+20);

          it +=1;
        }
      }
    }
  }
  glBindVertexArray(m_vao);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  //TODO is static draw the best? also is there a more dedicated function to do this?
  glBufferData(GL_ARRAY_BUFFER, verticies.size() * sizeof(float), &verticies[0], GL_STATIC_DRAW);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, index.size() * sizeof(unsigned short), &index[0], GL_STATIC_DRAW);
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  veolen = index.size();

  printf("updated chunk with %d cubes with %zu verticies(%zu bytes)\n", CCOUNTX*CCOUNTY*CCOUNTZ, verticies.size(),
          verticies.size()*sizeof(float));
}

void CubeChunk::draw(glm::mat4 camera) const {
  program->use();
  program->set_uniform("camera", camera);
  program->set_uniform("translate", translate);
  //texture->bind_texture(); //TODO sloooow
  glBindVertexArray(m_vao);
  //glDrawArrays(GL_TRIANGLES, 0, vbolen);
  glDrawElements(GL_TRIANGLES, veolen, GL_UNSIGNED_SHORT, 0);
  glBindVertexArray(0);
}
