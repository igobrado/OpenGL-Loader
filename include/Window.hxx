#ifndef OPENGL_PBR_WINDOW_HXX
#define OPENGL_PBR_WINDOW_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>

#include "Camera.hxx"
#include "Event.hxx"

struct WindowContext
{
    std::uint32_t windowWidth;
    std::uint32_t windowHeight;

    std::int32_t bufferHeight;
    std::int32_t bufferWidth;
};

class Window
{
    friend Keyboard;
    friend Mouse;

public:
    Window(std::uint32_t windowWidth, std::uint32_t windowHeight, EventDispatcher& dispatcher);
    ~Window();

    operator GLFWwindow*();

    std::uint32_t getBufferWidth() const;
    std::uint32_t getBufferHeight() const;

    void toggleMouseVisible();

protected:
    void initialize();
    bool shouldCaptureMouseEvents();

private:
    GLFWwindow*   mMainWindow;
    WindowContext mWindowContext;
    bool          mCursorEnabled;

    EventDispatcher& mDispatcher;
};
#endif  // OPENGL_PBR_WINDOW_HXX
