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
      Mesh(std::string file_name);
      int verticies_count;
      void add_vertex(float x, float y, float z);
  };
}

#endif
