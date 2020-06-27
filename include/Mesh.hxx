#ifndef OPENGL_PBR_MESH_HXX
#define OPENGL_PBR_MESH_HXX

#include <GL/glew.h>
#include <vector>

class Mesh
{
public:
    Mesh();
    ~Mesh();
    void createMesh(std::vector<float>& vertices, std::vector<unsigned int>& indices);
    void renderMesh();
    void clearMesh();
private:
    unsigned int mVao;
    unsigned int mVbo;
    unsigned int mIbo;

    std::size_t  mIndexCount;
};


#endif //OPENGL_PBR_MESH_HXX
