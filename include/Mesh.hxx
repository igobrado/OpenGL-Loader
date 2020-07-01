#ifndef OPENGL_PBR_MESH_HXX
#define OPENGL_PBR_MESH_HXX

#include <GL/glew.h>

#include <vector>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    void createMesh(std::vector<float>& vertices, std::vector<std::uint32_t>& indices);
    void renderMesh();
    void clearMesh();

private:
    std::uint32_t mVao;
    std::uint32_t mVbo;
    std::uint32_t mIbo;

    std::size_t mIndexCount;
    enum class DrawType
    {
        GL_STATIC  = GL_STATIC_DRAW,
        GL_DYNAMIC = GL_DYNAMIC_DRAW
    };
    struct BindUnbindVAOCreateMesh
    {
        explicit BindUnbindVAOCreateMesh(std::uint32_t& vao)
        {
            glGenVertexArrays(1, &vao);
            glBindVertexArray(vao);
        }

        ~BindUnbindVAOCreateMesh()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    };

    struct BindUnbindIBOCreateMesh
    {
        BindUnbindIBOCreateMesh(unsigned int& ibo, std::vector<std::uint32_t>& indices, DrawType drawType)
        {
            glGenBuffers(1, &ibo);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
            glBufferData(
                    GL_ELEMENT_ARRAY_BUFFER,
                    indices.size() * sizeof(indices[0]),
                    indices.data(),
                    drawType == DrawType::GL_STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        }

        ~BindUnbindIBOCreateMesh()
        {
            // UNBIND IBO
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    };

    struct BindUnbindVBOCreateMesh
    {
        BindUnbindVBOCreateMesh(std::uint32_t& vbo, std::vector<float>& vertices, DrawType drawType)
        {
            glGenBuffers(1, &vbo);
            glBindBuffer(GL_ARRAY_BUFFER, vbo);
            glBufferData(
                    GL_ARRAY_BUFFER,
                    vertices.size() * sizeof(vertices[0]),
                    vertices.data(),
                    drawType == DrawType::GL_STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW);
        }

        ~BindUnbindVBOCreateMesh()
        {
            glBindBuffer(GL_ARRAY_BUFFER, 0);
        }
    };

    struct BindUnbindVertexAttribPointerCreateMesh
    {
        BindUnbindVertexAttribPointerCreateMesh(
                unsigned int index,
                int          size,
                GLenum       type,
                bool         normalized,
                int          stride,
                const void*  ptr)
            : mIndex{ index }
        {
            glVertexAttribPointer(index, size, type, false, stride, ptr);
        }

        ~BindUnbindVertexAttribPointerCreateMesh()
        {
            glEnableVertexAttribArray(mIndex);
        }

    private:
        unsigned int mIndex;
    };
    struct BindVAORenderMesh
    {
        explicit BindVAORenderMesh(std::uint32_t& vao)
        {
            glBindVertexArray(vao);
        }

        ~BindVAORenderMesh()
        {
            glBindVertexArray(0);
        }
    };

    struct BindIBORenderMesh
    {
        explicit BindIBORenderMesh(std::uint32_t& ibo)
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo);
        }
        ~BindIBORenderMesh()
        {
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
        }
    };
};

#endif  // OPENGL_PBR_MESH_HXX
