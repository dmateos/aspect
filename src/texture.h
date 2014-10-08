#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "main.h"

namespace aspect {
  class Texture {
    public:
      Texture(const std::string &path);
      void bind_texture();
    private:
      GLuint m_tex;
  };

  class TextureAtlas : public Texture {
    public:
      TextureAtlas(const std::string &path);
      glm::vec4 get_tile(int w, int h, int x, int y) const;
    private:
      int width, height;
  };
};
#endif
