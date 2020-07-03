#ifndef OPENGL_PBR_MESH_HXX
#define OPENGL_PBR_MESH_HXX

#include <GL/glew.h>

#include <memory>
#include <vector>

#include "GLError.hxx"
#include "Texture.hxx"
#include "property/Material.hxx"

class Mesh
{
public:
    Mesh();
    Mesh(std::vector<float>& vertices, std::vector<std::uint32_t>& indices);
    Mesh(std::vector<float>& vertices, std::vector<std::uint32_t>& indices, Texture texture);
    Mesh(std::vector<float>& vertices, std::vector<std::uint32_t>& indices, Texture texture, Material material);

    void createMesh(std::vector<float>& vertices, std::vector<std::uint32_t>& indices);
    void renderMesh();
    void clearMesh();

    void setTexture(Texture texture);
    void setMaterial(Material material);

private:
    struct Vao
    {
        ~Vao()
        {
            glDeleteVertexArrays(0, *this);
        }

        operator std::uint32_t &()
        {
            return vao;
        }

        operator std::uint32_t *()
        {
            return &vao;
        }

        std::uint32_t vao;
    } mVao;

    struct BufferObject
    {
        ~BufferObject()
        {
            glDeleteBuffers(1, *this);
        }

        operator std::uint32_t &()
        {
            return bufferObject;
        }

        operator std::uint32_t *()
        {
            return &bufferObject;
        }
        std::uint32_t bufferObject;
    };

    BufferObject              mIbo;
    BufferObject              mVbo;
    std::size_t               mIndexCount;
    std::unique_ptr<Texture>  mTexture;
    std::unique_ptr<Material> mMaterial;
    enum class DrawType
    {
        GL_STATIC  = GL_STATIC_DRAW,
        GL_DYNAMIC = GL_DYNAMIC_DRAW
    };
    struct BindUnbindVAOCreateMesh
    {
        explicit BindUnbindVAOCreateMesh(std::uint32_t& vao)
        {
            GlCall(glGenVertexArrays(1, &vao));
            GlCall(glBindVertexArray(vao));
        }

        ~BindUnbindVAOCreateMesh()
        {
            GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }
    };

    struct BindUnbindIBOCreateMesh
    {
        BindUnbindIBOCreateMesh(unsigned int& ibo, std::vector<std::uint32_t>& indices, DrawType drawType)
        {
            GlCall(glGenBuffers(1, &ibo));
            GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
            GlCall(glBufferData(
                    GL_ELEMENT_ARRAY_BUFFER,
                    indices.size() * sizeof(indices[0]),
                    indices.data(),
                    drawType == DrawType::GL_STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
        }

        ~BindUnbindIBOCreateMesh()
        {
            // UNBIND IBO
            GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }
    };

    struct BindUnbindVBOCreateMesh
    {
        BindUnbindVBOCreateMesh(std::uint32_t& vbo, std::vector<float>& vertices, DrawType drawType)
        {
            GlCall(glGenBuffers(1, &vbo));
            GlCall(glBindBuffer(GL_ARRAY_BUFFER, vbo));
            GlCall(glBufferData(
                    GL_ARRAY_BUFFER,
                    vertices.size() * sizeof(vertices[0]),
                    vertices.data(),
                    drawType == DrawType::GL_STATIC ? GL_STATIC_DRAW : GL_DYNAMIC_DRAW));
        }

        ~BindUnbindVBOCreateMesh()
        {
            GlCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
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
            GlCall(glVertexAttribPointer(index, size, type, false, stride, ptr));
        }

        ~BindUnbindVertexAttribPointerCreateMesh()
        {
            GlCall(glEnableVertexAttribArray(mIndex));
        }

    private:
        unsigned int mIndex;
    };
    struct BindVAORenderMesh
    {
        explicit BindVAORenderMesh(std::uint32_t& vao)
        {
            GlCall(glBindVertexArray(vao));
        }

        ~BindVAORenderMesh()
        {
            GlCall(glBindVertexArray(0));
        }
    };

    struct BindIBORenderMesh
    {
        explicit BindIBORenderMesh(std::uint32_t& ibo)
        {
            GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo));
        }
        ~BindIBORenderMesh()
        {
            GlCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
        }
    };
};

#endif  // OPENGL_PBR_MESH_HXX
