#include "OpenGLPBR.hxx"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "EventSystem/MoveEvents.hxx"

#define VERTEX_SHADER   "../res/vertex.glsl"
#define FRAGMENT_SHADER "../res/fragment.glsl"

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
    , mMeshList{}
    , mShaderList{ std::make_shared<Shader>(VERTEX_SHADER, FRAGMENT_SHADER) }
    , mDeltaTime{ 0.0f }
    , mLastTime{ 0.0f }
    , mFirstDraw{ true }
    , mLight{ glm::vec3(1.0f,1.0f,1.0f),
              0.5f,
              mShaderList[0],
              glm::vec3{0.0f, 0.0f, -1.0f},
              0.5f }
    , mLights{}
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


    mLights.push_back(std::make_unique<PointLight>(
            glm::vec3{0.0f, 0.0f, 1.0f},
            0.0f,
            mShaderList[0],
            0.0f,
            glm::vec3{0.0f, 0.0f, 0.0f},
            0.3f,
            0.2f,
            0.1f,
            0));
    mLights.push_back(std::make_unique<PointLight>(
            glm::vec3{0.0f, 1.0f, 0.0f},
            0.0f,
            mShaderList[0],
            0.0f,
            glm::vec3{-4.0f, 2.0f, 0.0f},
            0.3f,
            0.1f,
            0.1f,
            1));

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
    int       i = 0;

    if (mImGui.resetCameraPosition())
    {
        mCamera.resetCameraContext();
    }

    mShaderList[0]->updateGlUniformMat4(uView, 1, false, mCamera.claculateViewMatrix());
    unsigned int t = mLights.size();
    mShaderList[0]->updateGlUniform1i(uPointLightCount, t);

    for (int k = 0; k < t; ++k)
    {
        mLights[k]->use();
    }
    mLight.use();
    for (auto& mesh : mMeshList)
    {

        mShaderList[0]->updateGlUniform3f(uEyePosition, mCamera.getCameraPosition());
        model = glm::translate(model, mImGui.getTranslateFactorVec3(i));
        if (mFirstDraw)
        {
            mFirstDraw = false;
        }
        model = glm::rotate(
                model,
                toRadians(mImGui.getRotationAngleControl()),
                mImGui.getRotationRotationFactorVec3());
        model = glm::rotate(model, toRadians(180), glm::vec3(0.0f, 0.0f, 1.0f));

        mShaderList[0]->updateGlUniformMat4(uModel, 1, false, model);
        mShaderList[0]->updateGlUniformMat4(uProjection, 1, false, projectionMatrix);
        mesh->renderMesh();
        model = glm::mat4{ 1.0f };
        i++;
    }
    mImGui.renderGui();
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
             //x     y     z        U     V       nx    ny    nz
            -1.0f, -1.0f, -0.6f,    0.0f, 0.0f,   0.0f, 0.0f, 0.0f,
             0.0f, -1.0f,  1.0f,    0.5f, 0.0f,   0.0f, 0.0f, 0.0f,
             1.0f, -1.0f, -0.6f,    1.0f, 0.0f,   0.0f, 0.0f, 0.0f,
             0.0f,  1.0f,  0.0f,    0.5f, 1.0f,   0.0f, 0.0f, 0.0f,
    };
    // clang-format on

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

    Texture brickTexture{ "../res/textures/brick.png" };
    Texture dirtTexture{ "../res/textures/plain.png" };

    auto mesh    = std::make_unique<Mesh>();
    auto meshTree = std::make_unique<Mesh>();
    calculateAvgNormals(indices, vertices, 8, 5);

    mesh->setTexture(brickTexture);
    mesh->setMaterial(Material{ 1.0f, 32.0f, mShaderList[0] });
    mesh->createMesh(vertices, indices);
    meshTree->setTexture(dirtTexture);
    meshTree->createMesh(florVertices, florIndices);
    mMeshList.push_back(std::move(mesh));
    mMeshList.push_back(std::move(meshTree));
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
