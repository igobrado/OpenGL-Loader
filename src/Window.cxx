#include "Window.hxx"

#include <sstream>

#include "EventSystem/MoveEvents.hxx"
#include "common/Logging.hxx"

Window::Window(
        std::uint32_t windowWidth,
        std::uint32_t windowHeight)  //
    : mWindowContext{ windowWidth, windowHeight, 0U, 0U, nullptr, nullptr }
    , mCursorEnabled{ false }
{
    initialize();
}

Window::~Window()
{
    glfwDestroyWindow(mWindowContext.mMainWindow);
    glfwTerminate();
}

Window::operator GLFWwindow*()
{
    return mWindowContext.mMainWindow;
}

void Window::setEventCallbackFunction(std::function<void(Event&)>&& eventCallbackFN)
{
    mWindowContext.eventCallbackFN = std::move(eventCallbackFN);
}

std::uint32_t Window::getBufferWidth() const
{
    return mWindowContext.bufferHeight;
}

std::uint32_t Window::getBufferHeight() const
{
    return mWindowContext.bufferHeight;
}

void Window::toggleMouseVisible()
{
    mCursorEnabled = !mCursorEnabled;
    glfwSetInputMode(
            mWindowContext.mMainWindow,
            GLFW_CURSOR,
            mCursorEnabled ? GLFW_CURSOR_NORMAL : GLFW_CURSOR_DISABLED);
}

void Window::initialize()
{
    if (!glfwInit())
    {
        OGL_CORE_ERROR("Error Initialising GLFW");
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
    mWindowContext.mMainWindow = glfwCreateWindow(
            mWindowContext.windowWidth,
            mWindowContext.windowHeight,
            "OpenGL-PBR",
            NULL,
            NULL);
    if (!mWindowContext.mMainWindow)
    {
        OGL_CORE_ERROR("Error creating GLFW window!");
        glfwTerminate();
    }

    // Get buffer size information
    glfwGetFramebufferSize(mWindowContext.mMainWindow, &mWindowContext.bufferWidth, &mWindowContext.bufferHeight);

    // Set the current context
    glfwMakeContextCurrent(mWindowContext.mMainWindow);

    glfwSetInputMode(mWindowContext.mMainWindow, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // Allow modern extension access
    glewExperimental = GL_TRUE;

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        OGL_CORE_ERROR("Error: %s", glewGetErrorString(error));
        glfwDestroyWindow(mWindowContext.mMainWindow);
        glfwTerminate();
    }

    glEnable(GL_DEPTH_TEST);

    // Create Viewport
    glViewport(0, 0, mWindowContext.bufferWidth, mWindowContext.bufferHeight);
    glfwSetWindowUserPointer(mWindowContext.mMainWindow, this);

    OGL_CORE_INFO("Window intiialized successfully, creating callbacks for keys and mouse move.\n");
    glfwSetKeyCallback(
            *this,
            [](GLFWwindow* window, int key, int code, int action, int mode)  //
            {                                                                //
                Window* theWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
                if (action == GLFW_PRESS || action == GLFW_REPEAT)
                {
                    KeyboardPressEvent event{ key, nullptr, theWindow, nullptr };
                    theWindow->mWindowContext.eventCallbackFN(event);
                }
                else if (action == GLFW_RELEASE)
                {
                    KeyboardReleaseEvent event{ key, nullptr, theWindow, nullptr };
                    theWindow->mWindowContext.eventCallbackFN(event);
                }
            });

    glfwSetCursorPosCallback(
            *this,
            [](GLFWwindow* window, double xPos, double yPos)  //
            {                                                 //
                Window*        theWindow = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
                MouseMoveEvent mouseMoveEvent{ nullptr, xPos, yPos };
                theWindow->mWindowContext.eventCallbackFN(mouseMoveEvent);
            });
}

bool Window::shouldCaptureMouseEvents()
{
    return !mCursorEnabled;
}