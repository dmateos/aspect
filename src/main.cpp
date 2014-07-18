#include "main.h"
#include "gl_program.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "util.h"

struct game_state {
  aspect::Camera camera;
} gs;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  const float step = 1.0;
  float yrotd, xrotd;

  switch(key) {
    case GLFW_KEY_W:
      gs.camera.offset_position(gs.camera.forward());
      break;
    case GLFW_KEY_A:
      gs.camera.offset_position(-gs.camera.right());
      break;
    case GLFW_KEY_S:
      gs.camera.offset_position(-gs.camera.forward());
      break;
    case GLFW_KEY_D:
      gs.camera.offset_position(gs.camera.right());
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
  double x, y;
  glfwGetCursorPos(window, &x, &y);
  gs.camera.offset_orientation(y * 1.0, x * 1.0);
  glfwSetCursorPos(window, 0.0f, 0.0f);
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

  if(!(window = glfwCreateWindow(XRES, YRES, "", NULL, NULL))) {
    std::cout << "could not make glfw window" << std::endl;
    return 1;
  }

  glfwMakeContextCurrent(window);
  glfwSetKeyCallback(window, key_callback);
  glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPos(window, 1024/2, 768/2);
  glewExperimental = GL_TRUE;
  glewInit();

  glEnable(GL_CULL_FACE);
  glCullFace(GL_FRONT);
  glEnable(GL_DEPTH_TEST);
  glDepthFunc(GL_LESS);
  print_gl_stats();

  /* Load our objects. */
  aspect::GLProgram program("shaders/vshader.test", "shaders/fshader.test");
  aspect::Mesh object_mesh("models/cube.dae");
  aspect::ModelAsset object_asset(&object_mesh, &program);

  std::vector<aspect::ModelInstance*> instances;

  aspect::Mesh cube_mesh("models/cube.dae");
  aspect::ModelAsset cube_asset(&cube_mesh, &program);

  for(float x = 0.0; x < 200.0; x+=4.0) {
    for(float z = 0.0; z < 200.0; z+=4.0) {
      aspect::ModelInstance *c = new aspect::ModelInstance(&cube_asset);
      c->transform = glm::translate(glm::mat4(1.0f), glm::vec3(x, -2.0f, z));
      instances.push_back(c);
    }
  }

  gs.camera.set_position(glm::vec3(50.0f, 0.0f, 60.0f));

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
