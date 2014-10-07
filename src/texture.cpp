#include "texture.h"
#include<IL/il.h>

using namespace aspect;

Texture::Texture(const std::string &path) {
  unsigned int imgid;
  bool ok;

  ilInit();
  ilGenImages(1, &imgid);
  ilBindImage(imgid);
  ok = ilLoadImage(path.c_str());

  if(!ok) {

  }

  glGenTextures(1, &m_tex);
  glBindTexture(GL_TEXTURE_2D, m_tex);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

  glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, ilGetInteger(IL_IMAGE_WIDTH), ilGetInteger(IL_IMAGE_HEIGHT), 
      0, GL_RGBA, GL_UNSIGNED_BYTE, ilGetData());

  glGenerateMipmap(GL_TEXTURE_2D);
  glBindTexture(GL_TEXTURE_2D, 0);
  printf("loaded texture %s\n", path.c_str());
}

void Texture::bind_texture() {
  glBindTexture(GL_TEXTURE_2D, m_tex);
}
