#include "main.h"
#include "gl_program.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"

void print_gl_stats() {
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);

  std::cout << renderer << std::endl;
  std::cout << version << std::endl;
}

int main(int argc, char **argv) {
  GLFWwindow *window;

  /* Setup all the opengl crap. */
  if(!glfwInit()) {
    std::cout << "could not start glfw3" << std::endl;
    return 1;
  }

  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

  if(!(window = glfwCreateWindow(1024, 768, "", NULL, NULL))) {
    std::cout << "could not make glfw window" << std::endl;
    return 1;
  }

  glfwMakeContextCurrent(window);
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  print_gl_stats();

  /* Load our objects. */
  aspect::GLProgram program("shaders/vshader.test", "shaders/fshader.test");
  aspect::Camera camera;

  aspect::Mesh monkey_mesh("models/monkey.dae");
  aspect::Mesh floor_mesh;

  floor_mesh.add_vertex(-1.0f,-1.0f,-1.0f);
  floor_mesh.add_vertex( 1.0f,-1.0f,-1.0f);
  floor_mesh.add_vertex(-1.0f,-1.0f, 1.0f);
  floor_mesh.add_vertex(1.0f,-1.0f,-1.0f);
  floor_mesh.add_vertex(1.0f,-1.0f, 1.0f);
  floor_mesh.add_vertex(-1.0f,-1.0f, 1.0f);

  aspect::ModelAsset monkey_asset(&monkey_mesh, &program);
  aspect::ModelAsset floor_asset(&monkey_mesh, &program);

  aspect::ModelInstance monkey_instance(&monkey_asset);
  aspect::ModelInstance floor_instance(&floor_asset);

  GLuint vao[2];
  glGenVertexArrays(1, &vao[0]);
  glBindVertexArray(vao[0]);

  GLuint vbo[2];
  glGenBuffers(1, &vbo[0]);
  glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);

  glBufferData(GL_ARRAY_BUFFER, monkey_mesh.verticies_count * 3 * sizeof(float), &monkey_mesh.verticies[0], GL_STATIC_DRAW);

  glEnableVertexAttribArray(program.get_attrib("vp"));
  glVertexAttribPointer(program.get_attrib("vp"), 3, GL_FLOAT, GL_FALSE, 0, NULL);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  program.use();
  glBindVertexArray(vao[0]);

//  camera.position_x(3.0f);
//  camera.position_y(3.0f);
  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glUniformMatrix4fv(program.get_uniform("transform"), 1, GL_FALSE, glm::value_ptr(camera.matrix()));
    glDrawArrays(GL_TRIANGLES, 0, monkey_mesh.verticies_count);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
