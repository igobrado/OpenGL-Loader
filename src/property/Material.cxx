#include "property/Material.hxx"

#include "Shader.hxx"
#include "UniformNames.hxx"

Material::Material(float startIntensity, float startShinines, std::shared_ptr<Shader>& shader)  //
    : mSpecularIntensity{ startIntensity }
    , mShinines{ startShinines }
    , mShader{ shader }
{
}

void Material::use()
{
    mShader->updateGlUniform1f(uSpecularIntensity, mShinines);
    mShader->updateGlUniform1f(uShininess, mShinines);
}