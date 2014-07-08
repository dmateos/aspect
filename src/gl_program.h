#ifndef _GL_SHADER_H_
#define _GL_SHADER_H_

#include <fstream>

#include "main.h"

namespace aspect {
  class GLProgram {
    private:
      GLuint vshader, fshader;
      GLint program;

      GLuint make_shader(std::string path, GLenum stype);
      GLint make_program(GLint vshader, GLint fshader);
    public:
      GLProgram(std::string vshader, std::string fshader);
      void use();
      GLint get_attrib(std::string attrib_name);
      GLint get_uniform(std::string attrib_name);
  };
};

#endif
