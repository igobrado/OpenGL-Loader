#include "Keyboard.hxx"

#include "Window.hxx"
#include "common/Logging.hxx"

Keyboard::Keyboard()  //
    : mKeys{ false }
{
}

void Keyboard::handleKeyboardKeys(GLFWwindow* window, int key, int code, int action, int mode)
{
    Window*   theWindow       = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    Keyboard& currentKeyboard = theWindow->getKeyboard();
    if (!window)
    {
        OGL_CORE_ERROR("Window user pointer was not set!\n");
        return;
    }

    if (action == GLFW_PRESS && key == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(*theWindow, GL_TRUE);
    }

    if ((key >= 0) && (key < currentKeyboard.mKeys.size()))
    {
        bool isKeyPressed = action == GLFW_PRESS;
        currentKeyboard.mKeys[key] = isKeyPressed;

        if (key == GLFW_KEY_SPACE && isKeyPressed)
        {
            theWindow->toggleMouseVisible();
        }
    }
}

Keyboard::operator GLFWkeyfun()
{
    return handleKeyboardKeys;
}

std::array<bool, 1024> &Keyboard::getKeys()
{
    return mKeys;
}

bool Keyboard::isKeyPressed(int code) const
{
    return mKeys[code];
}
