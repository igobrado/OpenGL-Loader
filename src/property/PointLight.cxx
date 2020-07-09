#include "property/PointLight.hxx"

PointLight::PointLight(
        glm::vec3                color,
        float                    aIntensity,
        std::shared_ptr<Shader>& shader,
        float                    dIntensity,
        glm::vec3                position,
        float                    constant,
        float                    linear,
        float                    exponent,
        int                      lightIndex)
    : Light{ color, aIntensity, shader, dIntensity }
    , mPosition{ position }
    , mConstant{ constant }
    , mLinear{ linear }
    , mExponent{ exponent }
    , mLightIndex{ lightIndex }
{
}

void PointLight::use()
{
    if (mShader)
    {
        auto& lightContext = mShader->getPointLightContext(mLightIndex);

        mShader->updateGlUniform3f(lightContext.uniformPosition, mPosition);
        mShader->updateGlUniform3f(lightContext.uniformColor, mColor);
        mShader->updateGlUniform1f(lightContext.uniformAmbientIntensity, mAmbientIntensity);
        mShader->updateGlUniform1f(lightContext.uniformDiffuseIntensity, mDiffuseIntensity);
        mShader->updateGlUniform1f(lightContext.uniformConstant, mConstant);
        mShader->updateGlUniform1f(lightContext.uniformLinear, mLinear);
        mShader->updateGlUniform1f(lightContext.uniformExponent, mExponent);
    }
}
