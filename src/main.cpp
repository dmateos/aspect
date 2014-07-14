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

aspect::Camera camera;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  float yrotd, xrotd;
  switch(key) {
    case GLFW_KEY_W:
      camera.translate(glm::vec3(0.0f, 0.0f, 0.1f));
      break;
    case GLFW_KEY_A:
      yrotd = (yrotd/180*3.14159);
      camera.translate(glm::vec3(cos(yrotd) * 0.2f, 0.0f, sin(yrotd) * 0.2f));
      break;
    case GLFW_KEY_S:
      camera.translate(glm::vec3(0.0f, 0.0f, -0.1f));
      break;
    case GLFW_KEY_D:
      yrotd = (yrotd/180*3.14159);
      camera.translate(glm::vec3(-cos(yrotd) * 0.2f, 0.0f, -sin(yrotd) * 0.2f));
      break;
  }
}


static void handle_mouse(GLFWwindow *window) {
  static double oldx, oldy;
  double diffx, diffy, x,y;

  if(diffx != oldx || diffy != oldy) {
    glfwGetCursorPos(window, &x, &y);
    diffx = x - oldx;
    diffy = y - oldy;

    camera.rotate(glm::vec3(diffx * 0.1, diffy * 0.1, 0.0f)); 
  }
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
  glfwSetKeyCallback(window, key_callback);
  glfwSetCursorPos(window, 0, 0);
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  print_gl_stats();

  /* Load our objects. */
  aspect::GLProgram program("shaders/vshader.test", "shaders/fshader.test");

  aspect::Mesh monkey_mesh("models/monkey.dae");

  aspect::ModelAsset monkey_asset(&monkey_mesh, &program);

  aspect::ModelInstance monkey_instance(&monkey_asset);
  monkey_instance.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f));
  aspect::ModelInstance monkey_instance2(&monkey_asset);
  monkey_instance2.transform = glm::translate(glm::mat4(1.0f), glm::vec3(+2.0f, 0.0f, 0.0f));

  std::vector<aspect::ModelInstance*> instances;
  instances.push_back(&monkey_instance);
  instances.push_back(&monkey_instance2);

  camera.translate(glm::vec3(0.0f, 0.0f, -5.0f));

  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::vector<aspect::ModelInstance*>::iterator it = instances.begin();
        it != instances.end(); it++) {
        aspect::ModelInstance *model = *it;

        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );

        model->asset->program->use();
        model->asset->program->set_uniform("transform", model->transform);
        model->asset->program->set_uniform("camera", camera.matrix());

        glBindVertexArray(model->asset->vao);
        glDrawArrays(GL_TRIANGLES, 0, model->asset->mesh->get_verticies_count());

        glBindVertexArray(0);
    }


  //  handle_mouse(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
