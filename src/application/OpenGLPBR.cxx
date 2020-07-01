#include "OpenGLPBR.hxx"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EventSystem/MoveEvents.hxx"

#define VERTEX_SHADER   "../res/vertex.glsl"
#define FRAGMENT_SHADER "../res/fragment.glsl"

OpenGLPBR::DefaultCameraContext::DefaultCameraContext()

    : startPosition{ 0.0f, 0.0f, 0.0f }
    , startUp{ 0.0f, -1.0f, 0.0f }
    , startYaw{ -90.0f }
    , startPitch{ 0.0f }
    , startMovementSpeed{ 5.0f }
    , startTurnSpeed{ 0.1f }
{
}

OpenGLPBR::OpenGLPBR(std::uint32_t windowWidth, std::uint32_t windowHeight)  //
    : mCamera{ DefaultCameraContext::context().startPosition,      DefaultCameraContext::context().startUp,
               DefaultCameraContext::context().startYaw,           DefaultCameraContext::context().startPitch,
               DefaultCameraContext::context().startMovementSpeed, DefaultCameraContext::context().startTurnSpeed }
    , mMouse{}
    , mKeyboard{}
    , mEventDispatcher{ std::make_shared<EventDispatcher>(mKeyboard, mMouse) }
    , mWindow{ std::make_unique<Window>(windowWidth, windowHeight) }
    , mImGui{ *mWindow, "#version 330", 2 }
    , mMeshList{}
    , mShaderList{}
    , mBrickTexture{"../res/textures/brick.png"}
    , mDirtTexture{"../res/textures/dirt.png"}
    , mVertexShader{ VERTEX_SHADER }
    , mFragmentShader{ FRAGMENT_SHADER }
    , mDeltaTime{ 0.0f }
    , mLastTime{ 0.0f }
    , mFirstDraw{true}

{
    mBrickTexture.loadTexture();
    mDirtTexture.loadTexture();
    auto eventCallbackFN = [this](Event& e) {
        switch (e.category())
        {
            case EventCategory::KEYBOARD:
                dynamic_cast<KeyboardEvent&>(e).setKeyboardHandle(&mKeyboard);
                dynamic_cast<KeyboardEvent&>(e).setMouseHandle(&mMouse);
                break;
            case EventCategory::MOUSE:
                dynamic_cast<MouseMoveEvent&>(e).setMouseHandle(&mMouse);
                dynamic_cast<MouseMoveEvent&>(e).setCameraUpdateCallback(mCamera.getOnMouseMoveCallbackFN());
                break;
            case EventCategory::CAMERA:
                break;
        }
        mEventDispatcher->dispatch(e);
    };

    mWindow->setEventCallbackFunction(std::move(eventCallbackFN));
    createObjects();
    createShaders();
}

OpenGLPBR::~OpenGLPBR()
{
    OGL_CORE_WARN("Terminating application.\n");
}

int OpenGLPBR::run()
{
    glm::mat4 projectionMatrix = glm::perspective(
            glm::radians(45.0f),
            (GLfloat) mWindow->getBufferWidth() / (GLfloat) mWindow->getBufferHeight(),
            0.1f,
            100.0f);
    while (!glfwWindowShouldClose(*mWindow))
    {
        float now  = glfwGetTime();
        mDeltaTime = now - mLastTime;
        mLastTime  = now;
        glfwPollEvents();

        mCamera.keyControl(mKeyboard, mDeltaTime);
        // mCamera.mouseControl(mMouse);
        update(projectionMatrix);
        glfwSwapBuffers(*mWindow);
    }
    return 0;
}

void OpenGLPBR::update(glm::mat4& projectionMatrix)
{
    auto screenColor = mImGui.getScreenColor();

    glClearColor(screenColor[0], screenColor[1], screenColor[2], screenColor[3]);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    mShaderList[0]->useShader();
    glm::mat4 model{ 1.0f };
    int       i = 0;

    if (mImGui.resetCameraPosition())
    {
        mCamera.resetCameraContext();
    }

    glUniformMatrix4fv(mShaderList[0]->getViewLocation(), 1, GL_FALSE, glm::value_ptr(mCamera.claculateViewMatrix()));

    for (auto& mesh : mMeshList)
    {
        if (!i)
            mBrickTexture.useTexture();
        else
            mDirtTexture.useTexture();
        model = glm::translate(model, mImGui.getTranslateFactorVec3(i));
        if (mFirstDraw)
        {

            mFirstDraw = false;
        }
        model = glm::rotate(model, toRadians(mImGui.getRotationAngle()), mImGui.getRotationRotationFactorVec3());
        model = glm::rotate(model, toRadians(180), glm::vec3(0.0f, 0.0f, 1.0f));
        model = glm::scale(model, mImGui.getScalingFactorByAxisVec3(i));

        glUniformMatrix4fv(mShaderList[0]->getModelMatrixLocation(), 1, GL_FALSE, glm::value_ptr(model));
        glUniformMatrix4fv(
                mShaderList[0]->getProjectionMatrixLocation(),
                1,
                GL_FALSE,
                glm::value_ptr(projectionMatrix));

        mesh->renderMesh();
        model = glm::mat4{ 1.0f };
        i++;
    }
    mImGui.renderGui();
}

void OpenGLPBR::createShaders()
{
    mShaderList.push_back(std::make_unique<Shader>());
    for (auto& shader : mShaderList)
    {
        shader->createShaderFromFile(mVertexShader, mFragmentShader);
    }
}

void OpenGLPBR::createObjects()
{
    // clang-format off
    std::vector<unsigned int> indices = {
            0, 3, 1,
            1, 3, 2,
            2, 3, 0,
            0, 1, 2
    };

    std::vector<float> vertices = {
             //x     y     z        U     v
            -1.0f, -1.0f, 0.0f,    0.0f, 0.0f,
             0.0f, -1.0f, 1.0f,    0.5,  0.0f,
             1.0f, -1.0f, 0.0f,    1.0f, 0.0f,
             0.0f,  1.0f, 0.0f,    0.5f, 1.0f,
    };
    // clang-format on

    mMeshList.push_back(std::make_unique<Mesh>());
    mMeshList.push_back(std::make_unique<Mesh>());

    for (auto& mesh : mMeshList)
    {
        mesh->createMesh(vertices, indices);
    }
}

constexpr float OpenGLPBR::toRadians(float angle)

{
    return (glm::pi<float>() / 180.0f) * angle;
}
