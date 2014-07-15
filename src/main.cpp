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

 void update_fps_counter(GLFWwindow* window) {
  static double previous_seconds = glfwGetTime ();
  static int frame_count;
  double current_seconds = glfwGetTime ();
  double elapsed_seconds = current_seconds - previous_seconds;

  if (elapsed_seconds > 0.25) {
    previous_seconds = current_seconds;
    double fps = (double)frame_count / elapsed_seconds;
    char tmp[128];
    sprintf (tmp, "opengl @ fps: %.2lf", fps);
    glfwSetWindowTitle (window, tmp);
    frame_count = 0;
  }
  frame_count++;
}

aspect::Camera camera;

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
  float yrotd, xrotd;
  yrotd = xrotd = 4.0;
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

  glfwGetCursorPos(window, &x, &y);
  if(x != oldx) {
    diffx = x - oldx;
    oldx = x;
    camera.rotate(glm::vec3(0.0f, diffx, 0.0f), 2.0f); 
  }

  /*
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
  aspect::Mesh object_mesh("models/torus.dae");
  aspect::ModelAsset object_asset(&object_mesh, &program);

  std::vector<aspect::ModelInstance*> instances;

  aspect::ModelInstance object_instance(&object_asset);
  object_instance.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, 0.0f));
  instances.push_back(&object_instance);

  aspect::ModelInstance object_instance2(&object_asset);
  object_instance2.transform = glm::translate(glm::mat4(1.0f), glm::vec3(+2.0f, 0.0f, 0.0f));
  instances.push_back(&object_instance2);

  aspect::ModelInstance object_instance3(&object_asset);
  object_instance3.transform = glm::translate(glm::mat4(1.0f), glm::vec3(+2.0f, 0.0f, -4.0f));
  instances.push_back(&object_instance3);

  aspect::ModelInstance object_instance4(&object_asset);
  object_instance4.transform = glm::translate(glm::mat4(1.0f), glm::vec3(-2.0f, 0.0f, -4.0f));
  instances.push_back(&object_instance4);

  camera.translate(glm::vec3(0.0f, 0.0f, -5.0f));

  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    for(std::vector<aspect::ModelInstance*>::iterator it = instances.begin();
        it != instances.end(); it++) {
        aspect::ModelInstance *model = *it;

        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE );

        model->asset->program->use();
        model->asset->program->set_uniform("transform", model->transform);
        model->asset->program->set_uniform("camera", camera.matrix());

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
