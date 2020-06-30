#include "Event.hxx"

#include "Window.hxx"

KeyboardEvent::KeyboardEvent(int action, int key, Keyboard& keyboard, Window& window)  //
    : mAction{ action }
    , mKey{ key }
    , mKeyboard{ keyboard }
    , mWindow{ window }
{
}

void KeyboardEvent::handle()
{
    if (mAction == GLFW_PRESS && mKey == GLFW_KEY_ESCAPE)
    {
        glfwSetWindowShouldClose(mWindow, GL_TRUE);
    }

    if ((mKey >= 0) && (mKey < mKeyboard.getKeys().size()))
    {
        bool isKeyPressed            = mAction == GLFW_PRESS;
        mKeyboard.getKeys().at(mKey) = isKeyPressed;

        if (mKey == GLFW_KEY_SPACE && isKeyPressed)
        {
            mWindow.toggleMouseVisible();
        }
    }
}

MouseMoveEvent::MouseMoveEvent(Mouse& mouse, double xPos, double yPos)  //
    : mMouse{ mouse }
    , mXPos{ xPos }
    , mYPos{ yPos }
{
}

void MouseMoveEvent::handle()
{
    auto& lastAndChangePoint = mMouse.getMouseContext();
    auto& lastPoint          = lastAndChangePoint.lastPoint;
    auto& changePoint        = lastAndChangePoint.changePoint;
    if (mMouse.mouseFirstMoved())
    {
        lastPoint.X = mXPos;
        lastPoint.Y = mYPos;
        mMouse.toggleMouseFirstMoved();
    }

    changePoint.X = mXPos - lastPoint.X;
    changePoint.Y = lastPoint.Y - mYPos;  /// TO AVOID INVERTED CAMERA

    lastPoint.X = mXPos;
    lastPoint.Y = mYPos;
}
