#include "EventSystem/Event.hxx"

#include "EventSystem/EventDispatcher.hxx"
#include "Window.hxx"

KeyboardEvent::KeyboardEvent(int key, Keyboard* keyboard, Window* window, Mouse* mouse)  //
    : mKey{ key }
    , mKeyboard{ keyboard }
    , mWindow{ window }
    , mMouse{ mouse }
{
}

std::string KeyboardEvent::toString()
{
    return std::string{ "Keyboard event. Pressed Key :" + std::to_string(mKey) };
}

void KeyboardEvent::setKeyboardHandle(Keyboard* keyboard)
{
    mKeyboard = keyboard;
}

void KeyboardEvent::setMouseHandle(Mouse* mouse)
{
    mMouse = mouse;
}

void KeyboardPressEvent::handle()
{
    if ((mKey >= 0) && (mKey < mKeyboard->getKeys().size()))
    {
        mKeyboard->getKeys().at(mKey) = true;
        if (mKey == GLFW_KEY_SPACE && glfwGetWindowAttrib(*mWindow, GLFW_FOCUSED))
        {
            mWindow->toggleMouseVisible();
            mMouse->toggleCaptureEvents();
        }
        else if (mKey == GLFW_KEY_ESCAPE)
        {
            glfwSetWindowShouldClose(*mWindow, true);
        }
    }
}

std::string KeyboardReleaseEvent::toString()
{
    return std::string{ "Keyboard event. Released Key :" + std::to_string(mKey) };
}

void KeyboardReleaseEvent::handle()
{
    if ((mKey >= 0) && (mKey < mKeyboard->getKeys().size()))
    {
        mKeyboard->getKeys().at(mKey) = false;
    }
}
