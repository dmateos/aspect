#include "gl_program.h"

aspect::GLProgram::GLProgram(std::string vshader, std::string fshader) {
  if((this->vshader = make_shader(vshader, GL_VERTEX_SHADER)) == -1) {
    std::cout << "could not load vshader " << vshader << std::endl;
  }

  if((this->fshader = make_shader(fshader, GL_FRAGMENT_SHADER)) == -1) {
    std::cout << "could not load fshader " << fshader << std::endl;
  }
}

GLint aspect::GLProgram::make_shader(std::string path, GLenum stype) {
  int length;
  const char *c_str;
  GLint shader_ok;
  GLuint shader = glCreateShader(stype);

  std::ifstream ifs(path);
  std::string data((std::istreambuf_iterator<GLchar>(ifs)),
                    (std::istreambuf_iterator<GLchar>()));

  length = data.length();

  c_str = data.c_str();
  glShaderSource(shader, 1, &c_str, &length);
  glCompileShader(shader);

  glGetShaderiv(shader, GL_COMPILE_STATUS, &shader_ok);

  if(!shader_ok) {
    std::cout << path << "did not compile" << std::endl;
    glDeleteShader(shader);
    return -1;
  }

  return shader;
}

GLint aspect::GLProgram::make_program(GLint vshader, GLint fshader) {
  GLint program_ok;
  GLint shader_program = glCreateProgram();
  glAttachShader(shader_program, vshader);
  glAttachShader(shader_program, fshader);
  glLinkProgram(shader_program);

  glGetProgramiv(shader_program, GL_LINK_STATUS, &program_ok);

  if(!program_ok) {
    std::cout << "program did not compile" << std::endl;
    return -1;
  }

  return shader_program;
};
