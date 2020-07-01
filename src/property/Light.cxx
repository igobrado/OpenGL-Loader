#include "property/Light.hxx"

Light::Light(glm::vec3& color, float& aIntensity, Shader* shader)  //
    : mColor{ color }
    , mAmbientIntensity{ aIntensity }
    , mShader{ shader }
{
}

void Light::useLight()
{
    if (mShader)
    {
        glUniform3f(mShader->getUniformAmbientColorLocation(), mColor.x, mColor.y, mColor.z);
        glUniform1f(mShader->getUniformAmbientIntensityLocation(), mAmbientIntensity);
    }
}

void Light::setShader(Shader* shader)
{
    mShader = shader;
}
