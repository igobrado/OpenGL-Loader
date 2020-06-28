#ifndef OPENGL_PBR_OPENGLPBR_HXX
#define OPENGL_PBR_OPENGLPBR_HXX

#include <cinttypes>
#include <memory>
#include <vector>

#include "IApplication.hxx"
#include "ImGuiAbstraction/ImGuiAbstraction.hxx"
#include "Mesh.hxx"
#include "Shader.hxx"
#include "Window.hxx"

class OpenGLPBR : public IApplication
{
public:
    OpenGLPBR(const std::uint32_t windowWidth, const std::uint32_t windowHeight);

    int run() override;

protected:
    int update() override;

    void createShaders();
    void createObject();

    constexpr float toRadians(float angle);

private:
    std::unique_ptr<Window> mWindow;
    gui::ImGuiAbstraction   mImGui;

    std::vector<std::unique_ptr<Mesh>>   mMeshList;
    std::vector<std::unique_ptr<Shader>> mShaderList;

    const char* mVertexShader;
    const char* mFragmentShader;
};

#endif  // OPENGL_PBR_OPENGLPBR_HXX
