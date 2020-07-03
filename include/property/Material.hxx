#ifndef OPENGL_PBR_MATERIAL_HXX
#define OPENGL_PBR_MATERIAL_HXX
#include <memory>

class Shader;

class Material
{
public:
    Material(float startIntensity, float startShinines, std::shared_ptr<Shader>& shader);
    void use();

private:
    float mSpecularIntensity;
    float mShinines;

    std::shared_ptr<Shader> mShader;
};

#endif  //! OPENGL_PBR_MATERIAL_HXX