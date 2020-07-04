#include "property/PointLight.hxx"

PointLight::PointLight(
        glm::vec3&               color,
        float&                   aIntensity,
        std::shared_ptr<Shader>& shader,
        float&                   diffuseIntensity,
        glm::vec3                position,
        float                    constant,
        float                    linear,
        float                    exponent)
    : Light{ color, aIntensity, shader, diffuseIntensity }
    , mPosition{ position }
    , mConstant{ constant }
    , mLinear{ linear }
    , mExponent{ exponent }
{
}

void PointLight::usePointLight()
{

}
