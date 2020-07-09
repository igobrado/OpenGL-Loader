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
#include "property/DirectionalLight.hxx"
#include "property/Material.hxx"
#include "property/PointLight.hxx"
#include "property/SpotLight.hxx"
#include "common/Model.hxx"

class OpenGLPBR : public IApplication
{
public:
    OpenGLPBR(const std::uint32_t windowWidth, const std::uint32_t windowHeight);
    ~OpenGLPBR();
    int run() override;

protected:
    void update(glm::mat4& projectionMatrix) override;

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

    std::unique_ptr<Mesh>   mFlor;
    std::vector<std::shared_ptr<Shader>> mShaderList;

    float            mDeltaTime;
    float            mLastTime;
    DirectionalLight mLight;
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

    std::vector<std::unique_ptr<Light>> mLights;

    std::vector<SpotLight> mSpotLights;

    Model mModel;
};

#endif  // OPENGL_PBR_OPENGLPBR_HXX
