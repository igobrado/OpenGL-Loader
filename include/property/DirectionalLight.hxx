#ifndef OPENGL_PBR_DIRECTIONALLIGHT_HXX
#define OPENGL_PBR_DIRECTIONALLIGHT_HXX

#include "Light.hxx"

class DirectionalLight : public Light
{
public:
    DirectionalLight(
            glm::vec3                color,
            float                    aIntensity,
            std::shared_ptr<Shader>& shader,
            glm::vec3                direction,
            float                    diffuseIntensity);

    void use() override;

private:
    glm::vec3 mDirection;
};
#endif  // OPENGL_PBR_DIRECTIONALLIGHT_HXX
