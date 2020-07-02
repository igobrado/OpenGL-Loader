#ifndef OPENGL_PBR_OPENGLPBR_HXX
#define OPENGL_PBR_OPENGLPBR_HXX

#include <cinttypes>
#include <memory>
#include <vector>

#include "EventSystem/EventDispatcher.hxx"
#include "IApplication.hxx"
#include "ImGuiAbstraction/ImGuiAbstraction.hxx"
#include "Mesh.hxx"
#include "Shader.hxx"
#include "Texture.hxx"
#include "Window.hxx"
#include "property/Light.hxx"

class OpenGLPBR : public IApplication
{
public:
    OpenGLPBR(const std::uint32_t windowWidth, const std::uint32_t windowHeight);
    ~OpenGLPBR();
    int run() override;

protected:
    void update(glm::mat4& projectionMatrix) override;

    void            createShaders();
    void            createObjects();
    constexpr float toRadians(float angle);

    void calculateAvgNormals(
            std::vector<unsigned int>& indices,
            std::vector<float>&        vetrices,
            unsigned int               vLength,
            unsigned int               normalOffset);

private:
    Camera   mCamera;
    Mouse    mMouse;
    Keyboard mKeyboard;

    std::shared_ptr<EventDispatcher> mEventDispatcher;

    std::unique_ptr<Window> mWindow;
    gui::ImGuiAbstraction   mImGui;

    std::vector<std::unique_ptr<Mesh>>   mMeshList;
    std::vector<std::unique_ptr<Shader>> mShaderList;
    const char*                          mVertexShader;
    const char*                          mFragmentShader;

    float mDeltaTime;
    float mLastTime;
    Light mLight;
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
    bool mFirstDraw;
};

#endif  // OPENGL_PBR_OPENGLPBR_HXX
