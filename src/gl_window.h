#ifndef _GL_WINDOW_H_
#define _GL_WINDOW_H_

#include "main.h"

namespace aspect {
  class GLWindow {
    public:
      GLWindow(int w, int h);
      GLFWwindow *get_window() { return window; }
      ~GLWindow();
      void update_fps_counter() const;
    private:
      GLFWwindow *window;
      void print_gl_stats() const;
  };
}

#endif

