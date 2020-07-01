
#include "EventSystem/MoveEvents.hxx"

MouseMoveEvent::MouseMoveEvent(Mouse* mouse, double xPos, double yPos)  //
    : mMouse{ mouse }
    , mXPos{ xPos }
    , mYPos{ yPos }
{
}

void MouseMoveEvent::setMouseHandle(Mouse* mouse)
{
    mMouse = mouse;
}

std::string MouseMoveEvent::toString()
{
    return std::string{ "Mouse event. PosX:" + std::to_string(static_cast<int>(mXPos))
                        + " PosY:" + std::to_string(static_cast<int>(mYPos)) };
}

void MouseMoveEvent::setCameraUpdateCallback(std::function<void(float, float,bool)>&& cameraUpdateCallback)
{
    mCameraUpdateCallback = std::move(cameraUpdateCallback);
}

void MouseMoveEvent::handle()
{
    auto& lastAndChangePoint = mMouse->getMouseContext();
    auto& lastPoint          = lastAndChangePoint.lastPoint;
    auto& changePoint        = lastAndChangePoint.changePoint;

    if (mMouse->mouseFirstMoved())
    {
        lastPoint.X = mXPos;
        lastPoint.Y = mYPos;
        mMouse->toggleMouseFirstMoved();
    }

    changePoint.X = lastPoint.X - mXPos;
    changePoint.Y = mYPos - lastPoint.Y;  /// TO AVOID INVERTED CAMERA

    lastPoint.X = mXPos;
    lastPoint.Y = mYPos;

    mCameraUpdateCallback(changePoint.X, changePoint.Y, mMouse->captureEvents());
}