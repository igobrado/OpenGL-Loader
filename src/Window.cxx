#include "Window.hxx"

#include "common/Logging.hxx"

Window::Window()  //
    : mMainWindow{ nullptr }
    , mWindowContext{ 800U, 600U, 0U, 0U }
{
    initialize();
}

Window::Window(std::uint32_t windowWidth, std::uint32_t windowHeight)  //
    : mMainWindow{ nullptr }
    , mWindowContext{ windowWidth, windowHeight, 0U, 0U }
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

std::uint32_t Window::getBufferWidth() const
{
    return mWindowContext.bufferHeight;
}

std::uint32_t Window::getBufferHeight() const
{
    return mWindowContext.bufferHeight;
}

void Window::initialize()
{
    if (!glfwInit())
    {
        OGL_CORE_ERROR("Error initialising GLFW!");
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
}
