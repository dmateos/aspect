#ifndef _MESH_H_
#define _MESH_H_

#include <vector>

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include "main.h"

namespace aspect {
  class Mesh {
    public:
      std::vector<float> m_verticies, m_normals, m_textures;
      std::vector<unsigned int> m_indeces;

      Mesh(const std::string &file_name);
      int get_verticies_count() const { return m_verticies_count; }
      int get_indeces_count() const { return m_indeces_count; }
      std::vector<float> *get_verticies() { return &m_verticies; }
      std::vector<float> *get_normals() { return &m_normals; }
      std::vector<float> *get_textures() { return &m_textures; } 
      std::vector<unsigned int> *get_indeces() { return &m_indeces; }

    private:
      unsigned int m_verticies_count;
      unsigned int m_indeces_count;
  };
}

#endif
