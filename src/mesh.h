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
      std::vector<float> verticies, normals, textures;

      Mesh();
      Mesh(const std::string &file_name);
      int get_verticies_count() { return verticies_count; }
      std::vector<float> *get_verticies() { return &verticies; }
      std::vector<float> *get_normals() { return &normals; }
      std::vector<float> *get_textures() { return &textures; } 

      void add_vert(float x, float y, float z); 

    private:
      int verticies_count;
  };
}

#endif
