#include "cube.h"

#include <string>
#include <string.h>
#include <iostream>

using namespace aspect;

/*
Cube::Cube() {
  float verts[] = {
    0.3f,0.3f,-0.3f, // topFront Right
    0.3f,-0.3f,-0.3f, //BottomFront Right
    -0.3f,-0.3f,-0.3f, //BottomFront Left
    -0.3f,0.3f,-0.3f,  //topFront Left
    0.3f,0.3f,0.3f, // topBack Right
    0.3f,-0.3f,0.3f, //BottomBack Right
    -0.3f,-0.3f,0.3f, //BottomBack Left
    -0.3f,0.3f,0.3f,  //topBack Left
  };

  float ind[] = {
    3,4,0, 0,4,1, 3,0,1,
    3,7,4, 7,6,4, 7,3,6,
    3,1,2, 1,6,2, 6,3,2,
    1,4,5, 5,6,1, 6,5,4    
  

  memcpy(verts, verticies, sizeof(verts));
  memcpy(ind, indeces, sizeof(indeces));
}
*/

CubeChunk::CubeChunk(GLProgram *program) : program(program){
  bool flip = 1;
  for(int x = 0; x < CSIZE; x++) {
    for(int y = 0; y < CSIZE; y++) {
      for(int z = 0; z < CSIZE; z++) {
        if(flip == 1) {
          m_cube[x][y][z] = 1;
          flip = 0;
        } else {
          m_cube[x][y][z] = 1;
          flip = 1;
        }
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

#define push_three(v, x,y,z)  v.push_back(x); v.push_back(y); v.push_back(z);

void CubeChunk::update() {
  for(int x = 0; x < CSIZE; x += 1) {
    for(int y = 0; y < CSIZE; y += 1) {
      for(int z = 0; z < CSIZE; z += 1) {
        if(m_cube[x][y][z] == 1) {
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+1.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+0.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+1.0f);
          push_three(m_verticies, x+0.0f,y+0.0f,z+0.0f);
          push_three(m_verticies, x+1.0f, y+0.0f,z+0.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+0.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f,y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+0.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+1.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+1.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+0.0f, y+0.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+0.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+0.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+1.0f,z+0.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+0.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+0.0f, y+1.0f, z+1.0f);
          push_three(m_verticies, x+1.0f, y+0.0f, z+1.0f);
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
