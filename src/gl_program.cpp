#include "gl_program.h"

using namespace aspect;

GLProgram::GLProgram(const std::string &vshader, const std::string &fshader) {
  if((m_vshader = make_shader(vshader, GL_VERTEX_SHADER)) == -1) {
    std::cout << "could not load vshader " << vshader << std::endl;
  }

  if((m_fshader = make_shader(fshader, GL_FRAGMENT_SHADER)) == -1) {
    std::cout << "could not load fshader " << fshader << std::endl;
  }
  //todo EXCEPTIONS

  if((m_program = make_program(m_vshader, m_fshader)) == -1) {
    std::cout << "could not make program" << std::endl;
  }

  std::cout << "loaded program with shader " << vshader << " and " << fshader << std::endl;;
}

void GLProgram::use() {
  glUseProgram(m_program);
}

GLint GLProgram::get_attrib(const std::string &attrib_name) const {
  GLint attrib = glGetAttribLocation(m_program, attrib_name.c_str());
  return attrib;
}

GLint GLProgram::get_uniform(const std::string &attrib_name) const {
  GLint attrib = glGetUniformLocation(m_program, attrib_name.c_str());
  return attrib;
}

void GLProgram::set_attrib(const std::string &attrib_name, const glm::mat4 &ptr) {
}

void GLProgram::set_uniform(const std::string &attrib_name, const glm::mat4 &ptr) {
  glUniformMatrix4fv(get_uniform(attrib_name), 1, GL_FALSE, glm::value_ptr(ptr));
}

GLuint GLProgram::make_shader(const std::string &path, GLenum stype) const {
  int length;
  const char *c_str;
  GLint shader_ok;
  GLuint shader = glCreateShader(stype);

  /* Load the shader from disk into a string. */
  std::ifstream ifs(path);
  std::string data((std::istreambuf_iterator<GLchar>(ifs)),
                    (std::istreambuf_iterator<GLchar>()));

  /* GL doesnt know what a c++ string is */
  length = data.length();
  c_str = data.c_str();

  glShaderSource(shader, 1, &c_str, &length);
  glCompileShader(shader);

  /* Check for compile issues. */
  glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);
  if(!shader_ok) {
    std::cout << path << "did not compile" << std::endl;
    glDeleteShader(shader);
    return -1;
  }

  return shader;
}

GLint GLProgram::make_program(GLint vshader, GLint fshader) const {
  GLint program_ok;
  GLint shader_program = glCreateProgram();

  glAttachShader(shader_program, vshader);
  glAttachShader(shader_program, fshader);
  glLinkProgram(shader_program);

  /* Did it work? */
  glGetProgramiv(shader_program, GL_LINK_STATUS, &program_ok);
  if(!program_ok) {
    std::cout << "program did not compile" << std::endl;
    return -1;
  }

  return shader_program;
};
