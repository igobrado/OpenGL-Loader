#ifndef OPENGL_PBR_WINDOW_HXX
#define OPENGL_PBR_WINDOW_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct WindowContext
{
    std::uint32_t windowWidth;
    std::uint32_t windowHeight;

    std::int32_t bufferHeight;
    std::int32_t bufferWidth;
};

class Window
{
public:
    Window();
    Window(std::uint32_t windowWidth, std::uint32_t windowHeight);
    ~Window();

    operator GLFWwindow*();
    inline std::uint32_t getBufferWidth() const;
    inline std::uint32_t getBufferHeight() const;

protected:
    void initialize();

private:
    GLFWwindow*   mMainWindow;
    WindowContext mWindowContext;
};
#endif  // OPENGL_PBR_WINDOW_HXX
