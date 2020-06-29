#include "Window.hxx"

#include <sstream>

#include "common/Logging.hxx"

Window::Window()  //
    : mCamera{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.f, 0.2f }
    , mMainWindow{ nullptr }
    , mWindowContext{ 800U, 600U, 0U, 0U }
    , mKeyboard{}
    , mMouse{}
    , mCursorEnabled{ false }

{
    initialize();
}

Window::Window(std::uint32_t windowWidth, std::uint32_t windowHeight)  //
    : mCamera{ glm::vec3(0.0f, 0.0f, 0.0f), glm::vec3(0.0f, 1.0f, 0.0f), -90.0f, 0.0f, 5.f, 0.2f }
    , mMainWindow{ nullptr }
    , mWindowContext{ windowWidth, windowHeight, 0U, 0U }
    , mKeyboard{}
    , mMouse{}
    , mCursorEnabled{ false }

{
    initialize();
}

Window::~Window()
{
    glfwDestroyWindow(mMainWindow);
    glfwTerminate();
}

Window::operator GLFWwindow*()
{
    return mMainWindow;
}

void Window::toggleMouseVisible()
{
    mCursorEnabled = !mCursorEnabled;
    glfwSetInputMode(mMainWindow, GLFW_CURSOR, !mCursorEnabled ? GLFW_CURSOR_DISABLED : GLFW_CURSOR_NORMAL);
}

std::uint32_t Window::getBufferWidth() const
{
    return mWindowContext.bufferHeight;
}

std::uint32_t Window::getBufferHeight() const
{
    return mWindowContext.bufferHeight;
}

Keyboard& Window::getKeyboard()
{
    return mKeyboard;
}

Mouse& Window::getMouse()
{
    return mMouse;
}

Camera& Window::getCamera()
{
    return mCamera;
}

void Window::initialize()
{
    if (!glfwInit())
    {
        printf("Error Initialising GLFW");
        glfwTerminate();
    }

    // Setup GLFW Windows Properties
    // OpenGL version
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    // Core Profile
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // Allow forward compatiblity
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

    // Create the window
    mMainWindow = glfwCreateWindow(mWindowContext.windowWidth, mWindowContext.windowHeight, "OpenGL-PBR", NULL, NULL);
    if (!mMainWindow)
    {
        OGL_CORE_ERROR("Error creating GLFW window!");
        glfwTerminate();
    }

    // Get buffer size information
    glfwGetFramebufferSize(mMainWindow, &mWindowContext.bufferWidth, &mWindowContext.bufferHeight);

    // Set the current context
    glfwMakeContextCurrent(mMainWindow);

    createCallbacks();
    glfwSetInputMode(mMainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Allow modern extension access
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        OGL_CORE_ERROR("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(mMainWindow);
        glfwTerminate();
    }

    glEnable(GL_DEPTH_TEST);

    // Create Viewport
    glViewport(0, 0, mWindowContext.bufferWidth, mWindowContext.bufferHeight);
    glfwSetWindowUserPointer(mMainWindow, this);
}

void Window::createCallbacks()
{
    glfwSetKeyCallback(mMainWindow, mKeyboard);
    glfwSetCursorPosCallback(mMainWindow, mMouse);
}

void Window::handleCameraEvents(float deltaTime)
{
    mCamera.keyControl(mKeyboard, deltaTime);
    mCamera.mouseControl(mMouse);
}
