#ifndef OPENGL_PBR_WINDOW_HXX
#define OPENGL_PBR_WINDOW_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>

#include "Camera.hxx"
#include "Keyboard.hxx"
#include "Mouse.hxx"

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

public:
    Window();
    Window(std::uint32_t windowWidth, std::uint32_t windowHeight);
    ~Window();

    operator GLFWwindow*();

    void handleCameraEvents(float deltaTime);
    std::uint32_t getBufferWidth() const;
    std::uint32_t getBufferHeight() const;

    Keyboard&     getKeyboard();
    Mouse&        getMouse();
    Camera&       getCamera();

protected:
    void toggleMouseVisible();
    void initialize();
    void createCallbacks();

private:
    Camera        mCamera;
    GLFWwindow*   mMainWindow;
    WindowContext mWindowContext;
    Keyboard      mKeyboard;
    Mouse         mMouse;

    bool mCursorEnabled;
};
#endif  // OPENGL_PBR_WINDOW_HXX
