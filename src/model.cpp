#include "model.h"

aspect::ModelAsset::ModelAsset(aspect::Mesh *mesh, aspect::GLProgram *program)
  : program(program), mesh(mesh)
{

  this->mesh = mesh;

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glBufferData(GL_ARRAY_BUFFER, mesh->verticies_count * 3 * sizeof(float),
               &mesh->verticies[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(program->get_attrib("vp"));
  glVertexAttribPointer(program->get_attrib("vp"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  //Cleanup
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

aspect::ModelInstance::ModelInstance(aspect::ModelAsset *asset)
  : asset(asset), translation(glm::mat4(1.0f))
{

}
