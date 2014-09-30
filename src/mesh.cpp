#include "mesh.h"

using namespace aspect;

Mesh::Mesh(const std::string &file_name) {
  const aiScene *scene = aiImportFile(file_name.c_str(), aiProcess_Triangulate | aiProcess_MakeLeftHanded);
  //const aiScene *scene = aiImportFile(file_name.c_str(), aiProcess_Triangulate);
  unsigned int g_point_count = 0;
  if(!scene) {
    fprintf(stderr, "error reading mesh %s\n", file_name.c_str());
  }

  m_indeces_count = 0;
  for(unsigned int mi = 0; mi < scene->mNumMeshes; mi++) {
    const aiMesh *mesh = scene->mMeshes[mi];
    //printf("%i verts in mesh\n", mesh->mNumVertices);

    g_point_count = mesh->mNumVertices;
    for(unsigned int vi = 0; vi < mesh->mNumVertices; vi++) {
      if(mesh->HasPositions()) {
        const aiVector3D *vp = &(mesh->mVertices[vi]);
        //printf ("vp %i (%f,%f,%f)\n", vi, vp->x, vp->y, vp->z);
        m_verticies.push_back(vp->x);
        m_verticies.push_back(vp->y);
        m_verticies.push_back(vp->z);
      }
      if(mesh->HasNormals()) {
        const aiVector3D *vn = &(mesh->mNormals[vi]);
        //printf("vn %i (%f,%f,%f)\n", vi, vn->x, vn->y, vn->z);
        m_normals.push_back(vn->x);
        m_normals.push_back(vn->y);
        m_normals.push_back(vn->z);
      }
      if(mesh->HasTextureCoords(0)) {
        const aiVector3D* vt = &(mesh->mTextureCoords[0][vi]);
        //printf("vt %i (%f, %f)\n", vi, vt->x, vt->y);
        m_textures.push_back(vt->x);
        m_textures.push_back(vt->y);
      }
      if(mesh->HasTangentsAndBitangents()) {

      }
    }

    if(mesh->HasFaces()) {
      for(unsigned int vi = 0; vi < mesh->mNumFaces; vi++) {
        struct aiFace *vf = mesh->mFaces + vi; 
        m_indeces.push_back(vf->mIndices[0]);
        m_indeces.push_back(vf->mIndices[1]);
        m_indeces.push_back(vf->mIndices[2]);
        //printf("vi %d %d %d\n", vf->mIndices[0], vf->mIndices[1], vf->mIndices[2]);
        m_indeces_count += 3;
      }
    }
  }

  m_verticies_count = g_point_count;
  aiReleaseImport(scene);

  std::cout << "loaded mesh " << file_name << std::endl;
}
