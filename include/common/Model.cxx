#include "Model.hxx"

Model::Model()  //
    : mMeshList{}
    , mTextureList{}
    , mMeshToTexture{}
{
}

void Model::loadModel(const char* fileName)
{
    Assimp::Importer importer{};
    const aiScene*   scene = importer.ReadFile(
            fileName,
            aiProcess_Triangulate                 //
                    | aiProcess_FlipUVs           //
                    | aiProcess_GenSmoothNormals  //
                    | aiProcess_JoinIdenticalVertices);

    if (!scene)
    {
        std::stringstream ss;
        ss << "Failed to load Model: " << importer.GetErrorString() << " Filename: " << fileName << std::endl;
        OGL_CORE_ERROR(ss.str().c_str());
        return;
    }
    loadNode(scene->mRootNode, scene);
    loadMaterials(scene);
}

void Model::renderModel()
{
    int i = 0;
    for (auto& mesh : mMeshList)
    {
        unsigned int materialIndex = mMeshToTexture[i];
        ++i;
        if (materialIndex < mTextureList.size() && mTextureList[materialIndex])
        {
            mTextureList[materialIndex]->useTexture();
        }
        mesh->renderMesh();
    }
}

void Model::loadNode(aiNode* node, const aiScene* scene)
{
    for (size_t i = 0; i < node->mNumMeshes; ++i)
    {
        loadMesh(scene->mMeshes[node->mMeshes[i]], scene);
    }

    for (size_t i = 0; i < node->mNumChildren; ++i)
    {
        loadNode(node->mChildren[i], scene);
    }
}

void Model::loadMesh(aiMesh* mesh, const aiScene* scene)
{
    std::vector<float>         vertices;
    std::vector<std::uint32_t> indices;

    for (size_t i = 0; i < mesh->mNumVertices; ++i)
    {
        vertices.insert(vertices.end(), { mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z });
        if (mesh->mTextureCoords[0])
        {
            vertices.insert(vertices.end(), { mesh->mTextureCoords[0][i].x, mesh->mTextureCoords[0][i].y });
        }
        else
        {
            vertices.insert(vertices.end(), { 0.0f, 0.0f });
        }
        vertices.insert(vertices.end(), { -mesh->mNormals[i].x, -mesh->mNormals[i].y, -mesh->mNormals[i].z });
    }
    for (size_t i = 0; i < mesh->mNumFaces; ++i)
    {
        aiFace face = mesh->mFaces[i];
        for (size_t j = 0; j < face.mNumIndices; ++j)
        {
            indices.push_back(face.mIndices[j]);
        }
    }

    mMeshList.push_back(std::make_unique<Mesh>(vertices, indices));
    mMeshToTexture.push_back(mesh->mMaterialIndex);
}

void Model::loadMaterials(const aiScene* scene)
{
    mTextureList.resize(scene->mNumMaterials);

    for (size_t i = 0; i < scene->mNumMaterials; ++i)
    {
        aiMaterial* material = scene->mMaterials[i];
        mTextureList[i]      = nullptr;
        if (material->GetTextureCount(aiTextureType_DIFFUSE))
        {
            aiString path;
            if (material->GetTexture(aiTextureType_DIFFUSE, 0, &path) == AI_SUCCESS)
            {
                int         idx      = std::string{ path.data }.rfind("\\");
                std::string filename = std::string(path.data).substr(idx + 1);
                std::string texPath  = std::string{ "/home/iob/Documents/dev/faks/OpenGL-PBR/res/textures/" }
                                      + filename;
                mTextureList[i] = std::make_shared<Texture>(
                        texPath.c_str(),
                        TextureType::TEXTURE_2D,
                        TextureRgbType::RGBA);

                if (!mTextureList[i]->loadTexture())
                {
                    std::stringstream ss;
                    ss << "Failed to load texture at: " << texPath.c_str() << std::endl;
                    OGL_CORE_ERROR(ss.str().c_str());
                }
            }
        }
        if (!mTextureList[i])
        {
            OGL_CORE_ERROR("No texture, continuing with plain\n");
            mTextureList[i] = std::make_shared<Texture>("../res/textures/plain.png");
            mTextureList[i]->loadTexture();
        }
    }
}