#ifndef OPENGL_PBR_MODEL_HXX
#define OPENGL_PBR_MODEL_HXX

#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <assimp/Importer.hpp>
#include <string>
#include <vector>

#include "Mesh.hxx"
#include "Texture.hxx"

class Model
{
public:
    Model();

    void loadModel(const char* fileName);
    void renderModel();

protected:
    void loadNode(aiNode* node, const aiScene* scene);
    void loadMesh(aiMesh* mesh, const aiScene* scene);
    void loadMaterials(const aiScene* scene);
private:
    std::vector<std::unique_ptr<Mesh>>    mMeshList;
    std::vector<std::shared_ptr<Texture>> mTextureList;

    std::vector<std::uint32_t> mMeshToTexture;
};

#endif  // OPENGL_PBR_MODEL_HXX
