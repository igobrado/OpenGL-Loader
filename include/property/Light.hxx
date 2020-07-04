#ifndef OPENGL_PBR_LIGHT_HXX
#define OPENGL_PBR_LIGHT_HXX

#include <GL/glew.h>

#include <glm/glm.hpp>
#include <memory>

#include "Shader.hxx"

class Light
{
public:
    Light(glm::vec3               color,
          float                   aIntensity,
          std::shared_ptr<Shader>& shader,
          float                   diffuseIntensity);
    virtual void use() = 0;


protected:
    glm::vec3 mColor;
    float     mAmbientIntensity;

    std::shared_ptr<Shader> mShader;

    float     mDiffuseIntensity;
};
#endif  // !OPENGL_PBR_MESH_HXX