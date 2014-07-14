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

  floor_mesh.add_vertex(-10.0f,-5.0f,-10.0f);
  floor_mesh.add_vertex( 10.0f,-5.0f,-10.0f);
  floor_mesh.add_vertex(-10.0f,-5.0f, 10.0f);
  floor_mesh.add_vertex(10.0f,-5.0f,-10.0f);
  floor_mesh.add_vertex(10.0f,-5.0f, 10.0f);
  floor_mesh.add_vertex(-10.0f,-5.0f, 10.0f);

  aspect::ModelAsset monkey_asset(&monkey_mesh, &program);
  aspect::ModelAsset floor_asset(&floor_mesh, &program);

  std::vector<aspect::ModelInstance*> instances;
  aspect::ModelInstance monkey_instance(&monkey_asset);
  aspect::ModelInstance floor_instance(&floor_asset);

  instances.push_back(&monkey_instance);
  //instances.push_back(&floor_instance);

  program.use();

//  camera.position_x(3.0f);
//  camera.position_y(3.0f);
//  camera.pitch(2.0f);
  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::vector<aspect::ModelInstance*>::iterator it = instances.begin();
        it != instances.end(); it++) {
        aspect::ModelInstance *model = *it;

        glPolygonMode( GL_FRONT_AND_BACK, GL_LINE );

        model->transform = glm::translate(glm::mat4(1.0f), glm::vec3(-1.0f, 0.0f, 0.0f));
        model->asset->program->use();
        model->asset->program->set_uniform("transform", model->transform);
        model->asset->program->set_uniform("camera", camera.matrix());

        glBindVertexArray(model->asset->vao);
        glDrawArrays(GL_TRIANGLES, 0, model->asset->mesh->verticies_count);

        glBindVertexArray(0);
    }


    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
