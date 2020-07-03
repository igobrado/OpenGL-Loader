#include "Mesh.hxx"

Mesh::Mesh()  //
    : mVao{ 0 }
    , mVbo{ 0 }
    , mIbo{ 0 }
    , mIndexCount{ 0 }
    , mTexture{ nullptr }
{
}

Mesh::Mesh(
        std::vector<float>&         vertices,  //
        std::vector<std::uint32_t>& indices)
    : mVao{ 0 }
    , mVbo{ 0 }
    , mIbo{ 0 }
    , mIndexCount{ 0 }
    , mTexture{ nullptr }
    , mMaterial{ nullptr }
{
    createMesh(vertices, indices);
}

Mesh::Mesh(
        std::vector<float>&         vertices,  //
        std::vector<std::uint32_t>& indices,   //
        Texture                     texture)
    : mVao{ 0 }
    , mVbo{ 0 }
    , mIbo{ 0 }
    , mIndexCount{ 0 }
    , mTexture{ std::make_unique<Texture>(texture) }
    , mMaterial{ nullptr }
{
    createMesh(vertices, indices);
}

Mesh::Mesh(
        std::vector<float>&         vertices,  //
        std::vector<std::uint32_t>& indices,
        Texture                     texture,
        Material                    material)
    : mVao{ 0 }
    , mVbo{ 0 }
    , mIbo{ 0 }
    , mIndexCount{ 0 }
    , mTexture{ std::make_unique<Texture>(texture) }
    , mMaterial{ std::make_unique<Material>(material) }
{
    createMesh(vertices, indices);
}

void Mesh::createMesh(std::vector<float>& vertices, std::vector<std::uint32_t>& indices)
{
    mIndexCount = indices.size();
    // BIND VAO - BINDS FIRST, UNBIND FOURTH
    BindUnbindVAOCreateMesh vaoBind{ mVao };

    // BIND IBO - BINDS SECOND, UNBIND THIRD
    BindUnbindIBOCreateMesh iboBind{ mIbo, indices, DrawType::GL_STATIC };

    // BIND VBO - BINDS THIRD, UNBIND SECOND
    BindUnbindVBOCreateMesh vboBind{ mVbo, vertices, DrawType::GL_STATIC };

    // BIND Vertex attrib pointer
    BindUnbindVertexAttribPointerCreateMesh bindVertexAttribPointer{
        0, 3, GL_FLOAT, false, sizeof(vertices[0]) * 8, 0
    };

    // BIND Vertex attrib pointer for texture
    BindUnbindVertexAttribPointerCreateMesh bindVertexAttribPointerForTextures{
        1, 2, GL_FLOAT, false, sizeof(vertices[0]) * 8, reinterpret_cast<void*>(sizeof(vertices[0]) * 3)
    };

    // BIND Vertex attrib pointer for light
    BindUnbindVertexAttribPointerCreateMesh bindVertexAttribPointerForLightning{
        2, 3, GL_FLOAT, false, sizeof(vertices[0]) * 8, reinterpret_cast<void*>(sizeof(vertices[0]) * 5)
    };
}

void Mesh::renderMesh()
{
    if (mTexture)
    {
        mTexture->useTexture();
    }

    if (mMaterial)
    {
        mMaterial->use();
    }

    // BIND VAO for rendering mesh - BOUND FIRST, UNBOUND LAST
    BindVAORenderMesh bindVaoRenderMesh{ mVao };
    // BIND IBO for rendering mesh - BOUND SECOND, UNBOUND FIRST
    BindIBORenderMesh bindIboRenderMesh{ mIbo };

    GlCall(glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0));
}

void Mesh::setTexture(Texture texture)
{
    mTexture = std::make_unique<Texture>(texture);
    mTexture->loadTexture();
}

void Mesh::setMaterial(Material material)
{
    mMaterial = std::make_unique<Material>(material);
}
