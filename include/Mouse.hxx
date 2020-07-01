#ifndef OPENGL_PBR_MOUSE_HXX
#define OPENGL_PBR_MOUSE_HXX

#include <GL/glew.h>
#include <GLFW/glfw3.h>

struct Point
{
    float X;
    float Y;
};

struct MouseContext
{
    Point lastPoint;
    Point changePoint;
};

class Mouse
{
public:
    Mouse();

    bool captureEvents();
    void toggleCaptureEvents();
    bool mouseFirstMoved();

    void  toggleMouseFirstMoved();
    float getXChange();
    float getYChange();

    MouseContext& getMouseContext();

private:
    MouseContext mMouseContext;
    bool         mShouldCaptureEvents;
    bool         mFirstMove;
};
#endif  // OPENGL_PBR_MOUSE_HXX
