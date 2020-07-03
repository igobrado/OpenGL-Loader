#include "property/Light.hxx"

#include "UniformNames.hxx"

Light::Light(
        glm::vec3&               color,
        float&                   aIntensity,
        std::shared_ptr<Shader>& shader,
        glm::vec3&               direction,
        float&                   diffuseIntensity)  //
    : mColor{ color }
    , mAmbientIntensity{ aIntensity }
    , mShader{ shader }
    , mDirection{ direction }
    , mDiffuseIntensity{ diffuseIntensity }
{
}

void Light::use()
{
    if (mShader)
    {
        mShader->updateGlUniform3f(uColor, mColor);
        mShader->updateGlUniform3f(uDirection, mDirection);
        mShader->updateUniform1f(uAmbientIntensity, mAmbientIntensity);
        mShader->updateUniform1f(uDiffuseIntensity, mDiffuseIntensity);
    }
}
