#include "property/SpotLight.hxx"

SpotLight::SpotLight(
        glm::vec3                color,
        float                    aIntensity,
        std::shared_ptr<Shader>& shader,
        float                    dIntensity,
        glm::vec3                position,
        float                    constant,
        float                    linear,
        float                    exponent,
        int                      lightIndex,
        glm::vec3                direction,
        float                    edge)
    : PointLight{ color, aIntensity, shader, dIntensity, position, constant, linear, exponent, lightIndex }
    , mDirection{ glm::normalize(direction) }
    , mEdge{ edge }
    , mProcessedEdge{ cosf(glm::radians(mEdge)) }
{
}

SpotLight::~SpotLight()
{
}

void SpotLight::use()
{
    if (mShader)
    {
        auto& lightContext = mShader->getSpotLightContext(mLightIndex);
        mShader->updateGlUniform3f(lightContext.uniformColor, mColor);
        mShader->updateGlUniform1f(lightContext.uniformAmbientIntensity, mAmbientIntensity);
        mShader->updateGlUniform1f(lightContext.uniformDiffuseIntensity, mDiffuseIntensity);

        mShader->updateGlUniform3f(lightContext.uniformPosition, mPosition);
        mShader->updateGlUniform1f(lightContext.uniformConstant, mConstant);
        mShader->updateGlUniform1f(lightContext.uniformLinear, mLinear);
        mShader->updateGlUniform1f(lightContext.uniformExponent, mExponent);

        mShader->updateGlUniform3f(lightContext.uniformDirection, mDirection);
        mShader->updateGlUniform1f(lightContext.uniformEdge, mProcessedEdge);
    }
}

void SpotLight::setFlash(glm::vec3 pos, glm::vec3 dir)
{
    mPosition  = pos;
    mDirection = dir;
}
