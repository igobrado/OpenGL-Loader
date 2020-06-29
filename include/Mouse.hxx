#ifndef OPENGL_PBR_MOUSE_HXX
#define OPENGL_PBR_MOUSE_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Point
{
    float X;
    float Y;
};

class Mouse
{
public:
    Mouse();
    operator GLFWcursorposfun();

    float getXChange();
    float getYChange();

protected:
    static void handleMouseMovement(GLFWwindow* window, double xPos, double yPos);

private:
    Point mLastPoint;
    Point mChangePoint;
    bool  mFirstMove;
};
#endif  // OPENGL_PBR_MOUSE_HXX
