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

void Mesh::createMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices)
{
    mIndexCount = indices.size();

    // BIND VAO
    glGenVertexArrays(1, &mVao);
    glBindVertexArray(mVao);

    // BIND IBO
    glGenBuffers(1, &mIbo);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(indices[0]), indices.data(), GL_STATIC_DRAW);

    // BIND VBO
    glGenBuffers(1, &mVbo);
    glBindBuffer(GL_ARRAY_BUFFER, mVbo);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(vertices[0]), vertices.data(), GL_STATIC_DRAW);

    // SET ATTRIB POINTER
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    // UNBIND VBO
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    // UNBIND IBO
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

    // UNBIND VAO
    glBindVertexArray(0);
}

void Mesh::renderMesh()
{
    glBindVertexArray(mVao);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mIbo);
    glDrawElements(GL_TRIANGLES, mIndexCount, GL_UNSIGNED_INT, 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
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
