#include "main.h"
#include "gl_program.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "util.h"

struct game_state {
  aspect::Camera camera;
  float yrot, xrot;
} gs;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  const float step = 1.0;
  float yrotd, xrotd;

  switch(key) {
    case GLFW_KEY_W:
      gs.camera.translate(glm::vec3(0.0f, 0.0f, step));
      break;
    case GLFW_KEY_A:
      //yrotd = (yrot/180*3.14159);
      //camera.translate(glm::vec3(cos(yrotd) * 0.2f, 0.0f, sin(yrotd) * 0.2f));
      gs.camera.translate(glm::vec3(1.0f, 0.0f, 0.0f));
      break;
    case GLFW_KEY_S:
      gs.camera.translate(glm::vec3(0.0f, 0.0f, -step));
      break;
    case GLFW_KEY_D:
      //yrotd = (yrot/180*3.14159);
      //camera.translate(glm::vec3(-cos(yrotd) * 0.2f, 0.0f, -sin(yrotd) * 0.2f));
      gs.camera.translate(glm::vec3(-1.0f, 0.0f, 0.0f));
      break;
    case GLFW_KEY_P:
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );
      break;
    case GLFW_KEY_O:
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL );
      break;
  }
}

static void handle_mouse(GLFWwindow *window) {
  static double oldx, oldy;
  double diffx, diffy, x,y;

  glfwGetCursorPos(window, &x, &y);
  if(x != oldx) {
    diffx = x - oldx;
    oldx = x;
    gs.camera.rotate(glm::vec3(0.0f, diffx, 0.0f), 2.0f); 
    gs.yrot += diffx;
  }

  /*
  aspect::Mesh object_mesh("models/monkey.dae");
  aspect::ModelAsset object_asset(&object_mesh, &program);
  if(y != oldy) {
    diffy = y - oldy;
    oldy = y;
    camera.rotate(glm::vec3(diffy, 0.0f, 0.0f)); 
  } */
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
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPos(window, 1024/2, 768/2);
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);

  print_gl_stats();

  /* Load our objects. */
  aspect::GLProgram program("shaders/vshader.test", "shaders/fshader.test");
  aspect::Mesh object_mesh("models/cube.dae");
  aspect::ModelAsset object_asset(&object_mesh, &program);

  std::vector<aspect::ModelInstance*> instances;

  aspect::ModelInstance object_instance(&object_asset);
  object_instance.transform = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 50.0f));
  instances.push_back(&object_instance);

  aspect::ModelInstance object_instance2(&object_asset);
  object_instance2.transform = glm::translate(glm::mat4(1.0f), glm::vec3(54.0f, 0.0f, 50.0f));
  instances.push_back(&object_instance2);

  aspect::ModelInstance object_instance3(&object_asset);
  object_instance3.transform = glm::translate(glm::mat4(1.0f), glm::vec3(50.0f, 0.0f, 54.0f));
  instances.push_back(&object_instance3);

  aspect::ModelInstance object_instance4(&object_asset);
  object_instance4.transform = glm::translate(glm::mat4(1.0f), glm::vec3(54.0f, 0.0f, 54.0f));
  instances.push_back(&object_instance4);

  aspect::Mesh cube_mesh("models/cube.dae");
  aspect::ModelAsset cube_asset(&cube_mesh, &program);
  for(float x = 0.0; x < 100.0; x+=4.0) {
    for(float z = 0.0; z < 100.0; z+=4.0) {
      aspect::ModelInstance *c = new aspect::ModelInstance(&cube_asset);
      c->transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, -2.0f, z));
      instances.push_back(c);
    }
  }

  gs.camera.translate(glm::vec3(-50.0f, 0.0f, -60.0f));

  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::vector<aspect::ModelInstance*>::iterator it = instances.begin();
        it != instances.end(); it++) {
        aspect::ModelInstance *model = *it;

        model->asset->program->use();
        model->asset->program->set_uniform("transform", model->matrix());
        model->asset->program->set_uniform("camera", gs.camera.matrix());

        glBindVertexArray(model->asset->vao);
        glDrawArrays(GL_TRIANGLES, 0, model->asset->mesh->get_verticies_count());

        glBindVertexArray(0);
    }

    handle_mouse(window);
    update_fps_counter(window);
    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
