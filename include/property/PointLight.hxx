#ifndef OPENGL_PBR_POINTLIGHT_HXX
#define OPENGL_PBR_POINTLIGHT_HXX

#include "Light.hxx"

class PointLight : public Light
{
public:
    PointLight(
            glm::vec3&               color,
            float&                   aIntensity,
            std::shared_ptr<Shader>& shader,
            float&                   diffuseIntensity,
            glm::vec3                position,
            float                    constant,
            float                    linear,
            float                    exponent);
    void use(){};

    virtual void usePointLight();
private:
    glm::vec3 mPosition;

    float mConstant;
    float mLinear;
    float mExponent;
};
#endif  // OPENGL_PBR_POINTLIGHT_HXX
