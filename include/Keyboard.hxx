#ifndef OPENGL_PBR_KEYBOARD_HXX
#define OPENGL_PBR_KEYBOARD_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <array>

class Keyboard
{
    friend class Camera;
public:
    Keyboard();
    operator GLFWkeyfun();

    bool isKeyPressed(int code) const;
    std::array<bool, 1024>& getKeys();

protected:
    static void handleKeyboardKeys(GLFWwindow* window, int key, int code, int action, int mode);

private:
    std::array<bool, 1024> mKeys;
};

#endif  // OPENGL_PBR_KEYBOARD_HXX
