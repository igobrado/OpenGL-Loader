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
    void update(glm::mat4& projectionMatrix) override;

    void            createShaders();
    void            createObjects();
    constexpr float toRadians(float angle);

private:
    Camera   mCamera;
    Mouse    mMouse;
    Keyboard mKeyboard;

    std::shared_ptr<EventDispatcher> mEventDispatcher;

    std::unique_ptr<Window> mWindow;
    gui::ImGuiAbstraction   mImGui;

    std::vector<std::unique_ptr<Mesh>>   mMeshList;
    std::vector<std::unique_ptr<Shader>> mShaderList;

    const char* mVertexShader;
    const char* mFragmentShader;

    float mDeltaTime;
    float mLastTime;

    struct DefaultCameraContext
    {

        static DefaultCameraContext& context()
        {
            static DefaultCameraContext ccontext;
            return ccontext;
        }
        const glm::vec3 startPosition;
        const glm::vec3 startUp;
        const float     startYaw;
        const float     startPitch;
        const float     startMovementSpeed;
        const float     startTurnSpeed;

    private:
        DefaultCameraContext();
    };
};

#endif  // OPENGL_PBR_OPENGLPBR_HXX
