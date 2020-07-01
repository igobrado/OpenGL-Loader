#ifndef OPENGL_PBR_LIGHT_HXX
#define OPENGL_PBR_LIGHT_HXX

#include <GL/glew.h>

#include <glm/glm.hpp>

#include "Shader.hxx"

class Light
{
public:
    Light(glm::vec3& color, float& aIntensity, Shader* shader);

    void useLight();

    void setShader(Shader* shader);

private:
    glm::vec3& mColor;
    float&     mAmbientIntensity;

    Shader* mShader;
};
#endif  // !OPENGL_PBR_MESH_HXX