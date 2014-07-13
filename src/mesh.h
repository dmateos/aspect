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
      Mesh(std::string file_name);

      std::vector<float> verticies, normals, textures;
      int verticies_count;
  };
}

#endif
