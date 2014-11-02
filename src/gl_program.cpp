#include "gl_program.h"

using namespace aspect;

GLProgram::GLProgram(const std::string &vshader, const std::string &fshader) {
  if((m_vshader = make_shader(vshader, GL_VERTEX_SHADER)) == 0) {
    printf("could not load vshader %s\n", vshader.c_str());
  }

  if((m_fshader = make_shader(fshader, GL_FRAGMENT_SHADER)) == 0) {
    printf("could not load fshader %s\n", fshader.c_str());
  }

  if((m_program = make_program(m_vshader, m_fshader)) == 0) {
    printf("could not make program\n");
  }

  printf("loaded progam with shader %s and %s\n", vshader.c_str(), fshader.c_str());
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
    printf("%s did not compile\n", path.c_str());
    glDeleteShader(shader);
    return 0;
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
    printf("program did not compile\n");
    return 0;
  }

  return shader_program;
};
