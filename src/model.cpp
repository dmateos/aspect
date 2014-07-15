#include "model.h"

using namespace aspect;

ModelAsset::ModelAsset(aspect::Mesh *mesh, aspect::GLProgram *program)
  : program(program), mesh(mesh)
{
  this->mesh = mesh;

  glGenBuffers(2, vbo);

  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, mesh->get_verticies_count() * 3 * sizeof(float),
              &mesh->verticies[0], GL_STATIC_DRAW);

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, mesh->get_verticies_count() * 3 * sizeof(float),
              &mesh->normals[0], GL_STATIC_DRAW);

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);

  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glEnableVertexAttribArray(program->get_attrib("vp"));
  glVertexAttribPointer(program->get_attrib("vp"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glEnableVertexAttribArray(program->get_attrib("nm"));
  glVertexAttribPointer(program->get_attrib("nm"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  //Cleanup
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  std::cout << "loaded new model asset" << std::endl;
}

ModelInstance::ModelInstance(aspect::ModelAsset *asset)
  : asset(asset), transform(glm::mat4(1.0f))
{
  std::cout << "loaded new model instance" << std::endl;
}

glm::mat4 ModelInstance::matrix() {
  return transform;
}
