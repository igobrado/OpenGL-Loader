#ifndef OPENGL_PBR_WINDOW_HXX
#define OPENGL_PBR_WINDOW_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <functional>

#include "Camera.hxx"
#include "EventSystem/Event.hxx"

struct WindowContext
{
    std::uint32_t windowWidth;
    std::uint32_t windowHeight;

    std::int32_t bufferHeight;
    std::int32_t bufferWidth;
    GLFWwindow*  mMainWindow;

    std::function<void(Event&)> eventCallbackFN;
};

class Window
{
    friend Keyboard;
    friend Mouse;

public:
    Window(std::uint32_t windowWidth, std::uint32_t windowHeight);
    ~Window();

    operator GLFWwindow*();

    void setEventCallbackFunction(std::function<void(Event&)>&& eventCallbackFN);

    std::uint32_t getBufferWidth() const;
    std::uint32_t getBufferHeight() const;

    void toggleMouseVisible();
    bool shouldCaptureMouseEvents();

protected:
    void initialize();

private:
    WindowContext mWindowContext;
    bool          mCursorEnabled;
};
#endif  // OPENGL_PBR_WINDOW_HXX
