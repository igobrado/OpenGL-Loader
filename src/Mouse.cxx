#include "Mouse.hxx"

#include <sstream>

#include "Window.hxx"

Mouse::Mouse()  //
    : mMouseContext{ Point{ 0.0f, 0.0f }, Point{ 0.0f, 0.0f } }
    , mFirstMove{ false }
    , mShouldCaptureEvents{ true }

{
}

bool Mouse::captureEvents()
{
    return mShouldCaptureEvents;
}

void Mouse::toggleCaptureEvents()
{
    mShouldCaptureEvents = !mShouldCaptureEvents;
}

bool Mouse::mouseFirstMoved()
{

    return mFirstMove;
}

void Mouse::toggleMouseFirstMoved()
{

    mFirstMove = !mFirstMove;
}

float Mouse::getXChange()
{
    float theChange             = mMouseContext.changePoint.X;
    mMouseContext.changePoint.X = 0.0f;
    return theChange;
}

float Mouse::getYChange()
{
    float theChange             = mMouseContext.changePoint.Y;
    mMouseContext.changePoint.Y = 0.0f;
    return theChange;
}

MouseContext& Mouse::getMouseContext()
{

    return mMouseContext;
}
