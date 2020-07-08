#include "property/Light.hxx"

Light::Light(
        glm::vec3                color,
        float                    aIntensity,
        std::shared_ptr<Shader>& shader,
        float                    dIntensity)  //
    : mColor{ color }
    , mAmbientIntensity{ aIntensity }
    , mShader{ shader }
    , mDiffuseIntensity{ dIntensity }
{
}
