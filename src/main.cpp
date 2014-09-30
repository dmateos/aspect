#include "main.h"
#include "gl_program.h"
#include "camera.h"
#include "mesh.h"
#include "model.h"
#include "util.h"
#include "cube.h"
#include "gl_window.h"

struct game_state {
  aspect::Camera camera;
  std::vector<aspect::ModelInstance*> model_instances;
  std::vector<aspect::CubeChunk*> cube_chunks;
  double delta_time;
} gs;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
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
  aspect::GLWindow window(1024, 768);
  glfwMakeContextCurrent(window.get_window());
  glfwSetKeyCallback(window.get_window(), key_callback);
  glfwSetInputMode(window.get_window(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetCursorPos(window.get_window(), 1024/2, 768/2);

  gs.camera.set_position(glm::vec3(+0.0f, +10.0f, +0.0f));
  double currentframe = glfwGetTime();
  double lastframe = currentframe;

  aspect::GLProgram monkey_program("shaders/vshader-nm.glsl", "shaders/fshader-nm.glsl");
  aspect::Mesh monkey_mesh("models/monkey.dae");
  aspect::ModelAsset monkey_asset(&monkey_mesh, &monkey_program);
  aspect::ModelInstance monkey(&monkey_asset);
  monkey.offset_position(glm::vec3(50, 0, 0));
  monkey.update();
  gs.model_instances.push_back(&monkey);

  aspect::GLProgram chunk_program("shaders/vshader.glsl", "shaders/fshader.glsl");
  for(int i = 0; i < 10; i++) {
    aspect::CubeChunk *chunk = new aspect::CubeChunk(&chunk_program, i*35, 0, 0);
    chunk->update();
    gs.cube_chunks.push_back(chunk);
  }

  while(!glfwWindowShouldClose(window.get_window())) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for_each(begin(gs.model_instances), end(gs.model_instances), [](aspect::ModelInstance *instance) {
      instance->draw(gs.camera.matrix());
    });

    for_each(begin(gs.cube_chunks), end(gs.cube_chunks), [](aspect::CubeChunk *chunk) { 
      chunk->draw(gs.camera.matrix());   
    });

    handle_mouse(window.get_window());
    update_fps_counter(window.get_window());
    glfwSwapBuffers(window.get_window());
    glfwPollEvents();

    currentframe = glfwGetTime();
    gs.delta_time = currentframe - lastframe;
    lastframe = currentframe;
  }

  return 0;
}
