#include "Mesh.hxx"

Mesh::Mesh()  //
    : mVao{ 0 }
    , mVbo{ 0 }
    , mIbo{ 0 }
    , mIndexCount{ 0 }
{
}

Mesh::~Mesh()
{
    clearMesh();
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

    // BIND Vertex attrib pointer, BIND FOURTH, UNBIND FIRST
    BindUnbindVertexAttribPointerCreateMesh bindVertexAttribPointer{ 0, 3, GL_FLOAT, false, 0, 0 };
}

void Mesh::renderMesh()
{
    // BIND VAO for rendering mesh - BOUND FIRST, UNBOUND LAST
    BindVAORenderMesh bindVaoRenderMesh{ mVao };
    // BIND IBO for rendering mesh - BOUND SECOND, UNBOUND FIRST
    BindIBORenderMesh bindIboRenderMesh{ mIbo };

    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
}

void Mesh::clearMesh()
{
    if (mIbo)
    {
        glDeleteBuffers(1, &mIbo);
        mIbo = 0;
    }

    if (mVbo)
    {
        glDeleteBuffers(1, &mVbo);
        mVbo = 0;
    }

    if (mVao)
    {
        glDeleteVertexArrays(1, &mVao);
        mVao = 0;
    }

    mIndexCount = 0;
}
