#include "main.h"

void print_gl_stats() {
  const GLubyte *renderer = glGetString(GL_RENDERER);
  const GLubyte *version = glGetString(GL_VERSION);

  std::cout << renderer << std::endl;
  std::cout << version << std::endl;
}

int main(int argc, char **argv) {
  GLFWwindow *window;

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

  aspect::GLProgram program("shaders/vshader.test", "shaders/fshader.test");

  while(!glfwWindowShouldClose(window)) {
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glfwSwapBuffers(window);
    glfwPollEvents();
  }

  glfwTerminate();
  return 0;
}
