#include "model.h"

using namespace aspect;

static const float maxvert = 85.0f; //gimbal lock :(

ModelAsset::ModelAsset(Mesh *mesh, GLProgram *program)
  : program(program), mesh(mesh)
{
  this->mesh = mesh;

  glGenVertexArrays(1, &vao);
  glBindVertexArray(vao);
  glGenBuffers(2, vbo);

  /* Verticies. */
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
  glBufferData(GL_ARRAY_BUFFER, mesh->get_verticies_count() * 3 * sizeof(float),
              &mesh->m_verticies[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(program->get_attrib("vp"));
  glVertexAttribPointer(program->get_attrib("vp"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  /* Normals */
  glBindBuffer(GL_ARRAY_BUFFER, vbo[1]);
  glBufferData(GL_ARRAY_BUFFER, mesh->get_verticies_count() * 3 * sizeof(float),
              &mesh->m_normals[0], GL_STATIC_DRAW);
  glEnableVertexAttribArray(program->get_attrib("nm"));
  glVertexAttribPointer(program->get_attrib("nm"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  /* Index buffers */
  glGenBuffers(1, &m_veo);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_veo);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, mesh->get_indeces_count() * sizeof(unsigned int),
              &mesh->m_indeces[0], GL_STATIC_DRAW);

  //Cleanup
  glBindVertexArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  printf("loaded new model asset with %d verticies and %d indeces\n", mesh->get_verticies_count(),
      mesh->get_indeces_count());
}

ModelInstance::ModelInstance(ModelAsset *asset) :
  asset(asset),
  m_position(0.0f, 0.0f, 0.0f),
  m_horizontalangle(0.0f),
  m_verticalangle(0.0f),
  m_matrix()
{
  std::cout << "loaded new model instance" << std::endl;
}

void ModelInstance::set_position(const glm::vec3 &position) {
  m_position = position;
}

void ModelInstance::offset_position(const glm::vec3 &position) {
  m_position += position;
}

glm::vec3 ModelInstance::get_position() const {
  return m_position;
}

void ModelInstance::scale(float n) {

}

glm::mat4 ModelInstance::orientation() const {
  glm::mat4 orientation;
  orientation = glm::rotate(orientation, m_verticalangle, glm::vec3(1,0,0));
  orientation = glm::rotate(orientation, m_horizontalangle, glm::vec3(0,1,0));
  return orientation;
}

void ModelInstance::offset_orientation(float up, float right) {
  m_horizontalangle += right;
  m_verticalangle += up;
  normalize();
}

glm::vec3 ModelInstance::forward() const {
  glm::vec4 forward = orientation() * glm::vec4(0,0,-1,1);
  return glm::vec3(forward);
}

glm::vec3 ModelInstance::right() const {
  glm::vec4 right = orientation() * glm::vec4(1,0,0,1);
  return glm::vec3(right);
}

glm::vec3 ModelInstance::up() const {
  glm::vec4 up = orientation() * glm::vec4(0,1,0,1);
  return glm::vec3(up);
}

void ModelInstance::update() {
  m_matrix = orientation() * glm::translate(glm::mat4(), m_position);
}

glm::mat4 ModelInstance::matrix() const {
  return m_matrix;
}

void ModelInstance::normalize() {
  m_horizontalangle = fmodf(m_horizontalangle, 360.0f);
  if(m_horizontalangle < 0.0f)
    m_horizontalangle += 360.0f;

  if(m_verticalangle > maxvert)
    m_verticalangle = maxvert;
  else if(m_verticalangle < - maxvert)
    m_verticalangle = -maxvert;
}

void ModelInstance::draw(glm::mat4 camera) {
  asset->program->use();
  asset->program->set_uniform("transform", matrix());
  asset->program->set_uniform("camera", camera);
  glBindVertexArray(asset->vao);
  glDrawElements(GL_TRIANGLES, asset->mesh->get_indeces_count(), GL_UNSIGNED_INT, 0);
  glBindVertexArray(0);
}
