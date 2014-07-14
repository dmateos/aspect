#include "mesh.h"

aspect::Mesh::Mesh(const std::string &file_name) {
  const aiScene *scene = aiImportFile(file_name.c_str(), aiProcess_Triangulate | aiProcess_MakeLeftHanded);
  //const aiScene *scene = aiImportFile(file_name.c_str(), aiProcess_Triangulate);
  unsigned int g_point_count = 0;
  if(!scene) {
    fprintf(stderr, "error reading mesh %s\n", file_name.c_str());
  }

  /*
  15   printf("%i animations\n", scene->mNumAnimations);
  16   printf("%i cameras\n", scene->mNumCameras);
  17   printf("%i lights\n", scene->mNumLights);
  18   printf("%i materials\n", scene->mNumMaterials);
  19   printf("%i meshes\n", scene->mNumMeshes);
  20   printf("%i textures\n", scene->mNumTextures);
  21   */

  for(unsigned int mi = 0; mi < scene->mNumMeshes; mi++) {
    const aiMesh *mesh = scene->mMeshes[mi];
    //printf("%i verts in mesh\n", mesh->mNumVertices);

    g_point_count = mesh->mNumVertices;
    for(unsigned int vi = 0; vi < mesh->mNumVertices; vi++) {
      if(mesh->HasPositions()) {
          const aiVector3D *vp = &(mesh->mVertices[vi]);
          //printf ("vp %i (%f,%f,%f)\n", vi, vp->x, vp->y, vp->z);
          verticies.push_back(vp->x);
          verticies.push_back(vp->y);
          verticies.push_back(vp->z);
        }
        if(mesh->HasNormals()) {
          const aiVector3D *vn = &(mesh->mNormals[vi]);
          //printf("vn %i (%f,%f,%f)\n", vi, vn->x, vn->y, vn->z);
          normals.push_back(vn->x);
          normals.push_back(vn->y);
          normals.push_back(vn->z);
        }
        if(mesh->HasTextureCoords(0)) {
          const aiVector3D* vt = &(mesh->mTextureCoords[0][vi]);
          //printf("vt %i (%f, %f)\n", vi, vt->x, vt->y);
          textures.push_back(vt->x);
          textures.push_back(vt->y);
        }
        if(mesh->HasTangentsAndBitangents()) {

        }
      }
    }
    verticies_count = g_point_count;
    aiReleaseImport(scene);
}

aspect::Mesh::Mesh() {

}
