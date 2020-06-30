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

    bool                    isKeyPressed(int code) const;
    std::array<bool, 1024>& getKeys();

private:
    std::array<bool, 1024> mKeys;
};

#endif  // OPENGL_PBR_KEYBOARD_HXX
