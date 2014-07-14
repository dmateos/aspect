#include "gl_program.h"

aspect::GLProgram::GLProgram(std::string vshader, std::string fshader) {
  if((this->vshader = make_shader(vshader, GL_VERTEX_SHADER)) == -1) {
    std::cout << "could not load vshader " << vshader << std::endl;
  }

  if((this->fshader = make_shader(fshader, GL_FRAGMENT_SHADER)) == -1) {
    std::cout << "could not load fshader " << fshader << std::endl;
  }
  //todo EXCEPTIONS

  if((this->program = make_program(this->fshader, this->vshader)) == -1) {
    std::cout << "could not make program" << std::endl;
  }
}

void aspect::GLProgram::use() {
  glUseProgram(this->program);
}

GLint aspect::GLProgram::get_attrib(std::string attrib_name) {
  GLint attrib = glGetAttribLocation(this->program, attrib_name.c_str());
  return attrib;
}

GLint aspect::GLProgram::get_uniform(std::string attrib_name) {
  GLint attrib = glGetUniformLocation(this->program, attrib_name.c_str());
  return attrib;
}

void aspect::GLProgram::set_attrib(std::string attrib_name, glm::mat4 ptr) {
}

void aspect::GLProgram::set_uniform(std::string attrib_name, glm::mat4 ptr) {
  glUniformMatrix4fv(get_uniform(attrib_name), 1, GL_FALSE, glm::value_ptr(ptr));
}

GLuint aspect::GLProgram::make_shader(std::string path, GLenum stype) {
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

GLint aspect::GLProgram::make_program(GLint vshader, GLint fshader) {
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
