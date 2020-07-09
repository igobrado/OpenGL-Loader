#ifndef OPENGL_PBR_POINTLIGHT_HXX
#define OPENGL_PBR_POINTLIGHT_HXX

#include "Light.hxx"

class PointLight : public Light
{
public:
    PointLight(
            glm::vec3                color,
            float                    aIntensity,
            std::shared_ptr<Shader>& shader,
            float                    dIntensity,
            glm::vec3                position,
            float                    constant,
            float                    linear,
            float                    exponent,
            int                      lightIndex);
    void use() override;

protected:
    glm::vec3 mPosition;

    float mConstant;
    float mLinear;
    float mExponent;

    int mLightIndex;
};
#endif  // OPENGL_PBR_POINTLIGHT_HXX
