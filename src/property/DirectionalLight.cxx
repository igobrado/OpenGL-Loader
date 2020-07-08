#include "property/DirectionalLight.hxx"

#include "UniformNames.hxx"
DirectionalLight::DirectionalLight(
        glm::vec3                color,
        float                    aIntensity,
        std::shared_ptr<Shader>& shader,
        glm::vec3                direction,
        float                    dIntensity)
    : Light{ color, aIntensity, shader, dIntensity }
    , mDirection{ direction }
{
}

void DirectionalLight::use()
{
    if (mShader)
    {
        mShader->updateGlUniform3f(uColor, mColor);
        mShader->updateGlUniform3f(uDirection, mDirection);
        mShader->updateGlUniform1f(uAmbientIntensity, mAmbientIntensity);
        mShader->updateGlUniform1f(uDiffuseIntensity, mDiffuseIntensity);
    }
}
