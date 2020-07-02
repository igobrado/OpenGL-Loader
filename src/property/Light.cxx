#include "property/Light.hxx"

Light::Light(glm::vec3& color, float& aIntensity, Shader* shader, glm::vec3 direction, float diffuseIntensity)  //
    : mColor{ color }
    , mAmbientIntensity{ aIntensity }
    , mShader{ shader }
    , mDirection{ direction }
    , mDiffuseIntensity{ diffuseIntensity }
{
}

void Light::useLight()
{
    if (mShader)
    {
        glUniform3f(mShader->getUniformColorLocation(), mColor.x, mColor.y, mColor.z);
        glUniform1f(mShader->getUniformAmbientIntensityLocation(), mAmbientIntensity);
        glUniform3f(mShader->getUniformDirectionLocation(), mDirection.x, mDirection.y, mDirection.z);
        glUniform1f(mShader->getUniformDiffuseIntensityLocation(), mDiffuseIntensity);
    }
}

void Light::setShader(Shader* shader)
{
    mShader = shader;
}
