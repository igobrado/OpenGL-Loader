#include "OpenGLPBR.hxx"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EventSystem/MoveEvents.hxx"

#define VERTEX_SHADER   "../res/vertex.glsl"
#define FRAGMENT_SHADER "../res/fragment.glsl"

#include <assimp/Importer.hpp>

#include "UniformNames.hxx"

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
    , mFlor{}
    , mShaderList{ std::make_shared<Shader>(VERTEX_SHADER, FRAGMENT_SHADER) }
    , mDeltaTime{ 0.0f }
    , mLastTime{ 0.0f }
    , mFirstDraw{ true }
    , mLight{ glm::vec3(1.0f, 1.0f, 1.0f), 0.8f, mShaderList[0], glm::vec3{ 0.0f, 0.0f, -1.0f }, 0.5f }
    , mLights{}
    , mSpotLights{}
{
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
    // mLights.push_back(std::make_unique<PointLight>(
    //        glm::vec3{ 0.0f, 1.0f, 0.0f },  /// color
    //        0.0f,                           /// ambient intensity
    //        mShaderList[0],                 /// shader
    //        0.1f,                           /// diffuse intensity
    //        glm::vec3{ 2.0f, 1.0f, 0.0f },  /// position
    //        0.3f,                           /// constant
    //        0.2f,                           /// linear
    //        0.1f,                           /// exponent
    //        0));                            /// index

    // mLights.push_back(std::make_unique<PointLight>(
    //         glm::vec3{ 1.0f, 0.0f, 0.0f },   /// color
    //         0.0f,                            /// ambient intensity
    //         mShaderList[0],                  /// shader
    //         0.1f,                            /// diffuse intensity
    //         glm::vec3{ -1.0f, 1.0f, 0.0f },  /// position
    //         0.3f,                            /// constant
    //         0.2f,                            /// linear
    //         0.1f,                            /// exponent
    //         0));                             /// index
    //
    mSpotLights.push_back(SpotLight(
            glm::vec3{ 1.0f, 1.0f, 1.0f },   /// color
            0.0f,                            /// ambient intensity
            mShaderList[0],                  /// shader
            1.0f,                            /// diffuse intensity
            glm::vec3{ 0.0f, -1.0f, 0.0f },  /// position
            1.0f,                            /// constant
            0.0f,                            /// linear
            0.0f,                            /// exponent
            0,                               /// index
            glm::vec3{ 1.0f, 0.0f, 0.0f },   /// direction
            10.f));                          /// edge

    mSpotLights.push_back(SpotLight(
            glm::vec3{ 1.0f, 1.0f, 1.0f },    /// color
            0.0f,                             /// ambient intensity
            mShaderList[0],                   /// shader
            1.0f,                             /// diffuse intensity
            glm::vec3{ 0.0f, 1.5f, 0.0f },    /// position
            0.0f,                             /// constant
            0.0f,                             /// linear
            0.1f,                             /// exponent
            1,                                /// index
            glm::vec3{ 100.0f, 1.0f, 0.0f },  /// direction
            10.f));                           /// edge

    mWindow->setEventCallbackFunction(std::move(eventCallbackFN));
    createObjects();
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

    if (mImGui.resetCameraPosition())
    {
        mCamera.resetCameraContext();
    }
    mShaderList[0]->updateGlUniformMat4(uView, 1, false, mCamera.claculateViewMatrix());
    unsigned int pointLightSize = mLights.size();
    unsigned int spotLightSize  = mSpotLights.size();

    mShaderList[0]->updateGlUniform1i(uPointLightCount, pointLightSize);
    mShaderList[0]->updateGlUniform1i(uSpotLightCount, spotLightSize);

    for (int k = 0; k < pointLightSize; ++k)
    {
        mLights[k]->use();
    }

    for (int k = 0; k < spotLightSize; ++k)
    {
        mSpotLights[k].use();
    }

    mLight.use();

    /// RENDER MESH
    mShaderList[0]->updateGlUniform3f(uEyePosition, mCamera.getCameraPosition());
    model = glm::translate(model, mImGui.getTranslateFactorVec3(0));
    if (mFirstDraw)
    {
        mFirstDraw = false;
    }
    model = glm::rotate(model, toRadians(mImGui.getRotationAngleControl()), mImGui.getRotationRotationFactorVec3());
    model = glm::rotate(model, toRadians(180), glm::vec3(0.0f, 0.0f, 1.0f));
    mShaderList[0]->updateGlUniformMat4(uModel, 1, false, model);
    mShaderList[0]->updateGlUniformMat4(uProjection, 1, false, projectionMatrix);
    mFlor->renderMesh();
    ///

    /// RENDER MODEL
    model = glm::mat4{ 1 };
    mShaderList[0]->updateGlUniform3f(uEyePosition, mCamera.getCameraPosition());
    model = glm::translate(model, glm::vec3(0, 0, 0));
    model = glm::rotate(model, toRadians(90), glm::vec3(1.0f, 0.0f, 0.0f));
    model = glm::scale(model, glm::vec3(0.5, 0.5, 0.5));
    mShaderList[0]->updateGlUniformMat4(uModel, 1, false, model);
    mShaderList[0]->updateGlUniformMat4(uProjection, 1, false, projectionMatrix);
    mModel.renderModel();
    ///
    mImGui.renderGui();
}

void OpenGLPBR::createObjects()
{
    // clang-format off
    std::vector<unsigned int> florIndices = {
            0, 2, 1,
            1, 2, 3
    };

    std::vector<float> florVertices = {
            //x     y     z        U     V       nx    ny    nz
            -10.0f,  0.0f, -10.0f,  0.0f ,  0.0f,  0.0f, -1.0f, 0.0f,
             10.0f,  0.0f, -10.0f,  10.0f,  0.0f,  0.0f, -1.0f, 0.0f,
            -10.0f,  0.0f,  10.0f,  0.0f ,  10.0f, 0.0f, -1.0f, 0.0f,
             10.0f,  0.0f,  10.0f,  10.0f,  10.0f, 0.0f, -1.0f, 0.0f
    };
    // clang-format on

    Texture dirtTexture{ "../res/textures/dirt.png", TextureType::TEXTURE_2D, TextureRgbType::RGBA };

    mFlor = std::make_unique<Mesh>();
    mFlor->setTexture(dirtTexture);
    mFlor->createMesh(florVertices, florIndices);
    mFlor->setMaterial(Material{ 4.0f, 256.0f, mShaderList[0] });

    mModel.loadModel("../res/Models/hammer.obj");
}

void OpenGLPBR::calculateAvgNormals(
        std::vector<unsigned int>& indices,
        std::vector<float>&        vertices,
        unsigned int               vLength,
        unsigned int               normalOffset)
{
    // clang-format off
    auto data = indices.data();
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        unsigned int in0 = data[i] * vLength;
        unsigned int in1 = data[i + 1] * vLength;
        unsigned int in2 = data[i + 2] * vLength;

        glm::vec3 v1{vertices[in1] - vertices[in0], vertices[in1 + 1] - vertices[in0 + 1], vertices[in1 + 2] - vertices[in0 + 2]};
        glm::vec3 v2{vertices[in2] - vertices[in0], vertices[in2 + 1] - vertices[in0 + 1], vertices[in2 + 2] - vertices[in0 + 2]};
        glm::vec3 normal = glm::cross(v1, v2);
        normal = glm::normalize(normal);

        vertices[in0 + normalOffset    ] += normal.x;
        vertices[in0 + normalOffset + 1] += normal.y;
        vertices[in0 + normalOffset + 2] += normal.z;

        vertices[in1 + normalOffset    ] += normal.x;
        vertices[in1 + normalOffset + 1] += normal.y;
        vertices[in1 + normalOffset + 2] += normal.z;

        vertices[in2 + normalOffset    ] += normal.x;
        vertices[in2 + normalOffset + 1] += normal.y;
        vertices[in2 + normalOffset + 2] += normal.z;
    }

    for (size_t i = 0; i < vertices.size() / vLength; i++)
    {
            unsigned int nOffset = i * vLength + normalOffset;
            glm::vec3 vec{vertices[nOffset], vertices[nOffset + 1], vertices[nOffset + 2]};
            vec = glm::normalize(vec);

            vertices[nOffset] = vec.x;
            vertices[nOffset + 1] = vec.y;
            vertices[nOffset + 2] = vec.z;
    }
    // clang-format on
}

constexpr float OpenGLPBR::toRadians(float angle)
{
    return (glm::pi<float>() / 180.0f) * angle;
}
