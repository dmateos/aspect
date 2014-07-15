#ifndef _GL_PROGRAM_H_
#define _GL_PROGRAM_H_

#include <fstream>

#include "main.h"

namespace aspect {
  class GLProgram {
   public:
      GLProgram(const std::string &vshader, const std::string &fshader);
      void use();
      GLint get_attrib(const std::string &attrib_name) const;
      GLint get_uniform(const std::string &attrib_name) const;
      void set_attrib(const std::string &attrib_name, const glm::mat4 &ptr);
      void set_uniform(const std::string &attrib_name, const glm::mat4 &ptr);

    private:
      GLuint m_vshader, m_fshader;
      GLint m_program;

      GLuint make_shader(const std::string &path, GLenum stype) const;
      GLint make_program(GLint vshader, GLint fshader) const;
    };
};

#endif
