#include "main.h"
#include "gl_program.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "util.h"
#include "cube.h"

struct game_state {
  aspect::Camera camera;
  std::vector<aspect::ModelInstance*> instances;
  double delta_time;
} gs;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  const float step = 1.0;
  float yrotd, xrotd;
  bool colision = false;

  switch(key) {
    case GLFW_KEY_W:
      gs.camera.offset_position(gs.camera.forward(1.0f));
      break;
    case GLFW_KEY_A:
      gs.camera.offset_position(-gs.camera.right(1.0f));
      break;
    case GLFW_KEY_S:
      gs.camera.offset_position(-gs.camera.forward(1.0f));
      break;
    case GLFW_KEY_D:
      gs.camera.offset_position(gs.camera.right(1.0f));
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

  /* Draw our cubes */
  aspect::GLProgram cube_program("shaders/vshader-nm.glsl", "shaders/fshader-nm.glsl");

  gs.camera.set_position(glm::vec3(+0.0f, +10.0f, +0.0f));
  double currentframe = glfwGetTime();
  double lastframe = currentframe;

  aspect::Mesh cube_mesh("models/cube.dae");
  aspect::ModelAsset cube_asset(&cube_mesh, &cube_program);
  for(float x = 0.0; x < 10.0; x += 1.0) {
    for(float y = 0.0; y < 10.0; y += 1.0) {
      for(float z = 0.0; z < 10.0; z += 1.0) {
        aspect::ModelInstance *c = new aspect::ModelInstance(&cube_asset);
        c->set_position(glm::vec3(x+30, y, z));
        c->update();
        gs.instances.push_back(c);
      }
    }
  }

  aspect::GLProgram chunk_program("shaders/vshader.glsl", "shaders/fshader.glsl");
  aspect::CubeChunk chunk(&chunk_program);
  chunk.update();

  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::vector<aspect::ModelInstance*>::iterator it = gs.instances.begin();
        it != gs.instances.end(); it++) {
       (*it)->draw(gs.camera.matrix());
    }

    chunk.draw(gs.camera.matrix());
    handle_mouse(window);
    update_fps_counter(window);
    glfwSwapBuffers(window);
    glfwPollEvents();

    currentframe = glfwGetTime();
    gs.delta_time = currentframe - lastframe;
    lastframe = currentframe;
  }

  glfwTerminate();
  return 0;
}
