#include "Mouse.hxx"

#include <sstream>

#include "Window.hxx"
#include "common/Logging.hxx"

Mouse::Mouse()  //
    : mLastPoint{ 0.0f, 0.0f }
    , mChangePoint{ 0.0f, 0.0f }
    , mFirstMove{ false }
{
}

Mouse::operator GLFWcursorposfun()
{
    return handleMouseMovement;
}

float Mouse::getXChange()
{
    float theChange = mChangePoint.X;
    mChangePoint.X  = 0.0f;
    return theChange;
}

float Mouse::getYChange()
{
    float theChange = mChangePoint.Y;
    mChangePoint.Y  = 0.0f;
    return theChange;
}

void Mouse::handleMouseMovement(GLFWwindow* window, double xPos, double yPos)
{
    Window* theWindow    = reinterpret_cast<Window*>(glfwGetWindowUserPointer(window));
    Mouse&  currentMouse = theWindow->getMouse();

    if (currentMouse.mFirstMove)
    {
        currentMouse.mLastPoint.X = xPos;
        currentMouse.mLastPoint.Y = yPos;
        currentMouse.mFirstMove   = false;
    }

    currentMouse.mChangePoint.X = xPos - currentMouse.mLastPoint.X;
    currentMouse.mChangePoint.Y = currentMouse.mLastPoint.Y - yPos;  /// TO AVOID INVERTED CAMERA

    currentMouse.mLastPoint.X = xPos;
    currentMouse.mLastPoint.Y = yPos;
    std::stringstream ss;
    ss << "Last point X: " << currentMouse.mLastPoint.X << " Last point Y: " << currentMouse.mLastPoint.Y << std::endl;
    OGL_CORE_INFO(ss.str().c_str());
}
