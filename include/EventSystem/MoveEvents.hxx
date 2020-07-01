#ifndef OPENGL_PBR_EVENT_MOVE_EVENTS_HXX
#define OPENGL_PBR_EVENT_MOVE_EVENTS_HXX

#include "Event.hxx"
#include "Mouse.hxx"

class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(Mouse* mouse, double xPos, double yPos);
    std::string   toString() override;
    EventCategory category() override
    {
        return EventCategory::MOUSE;
    }

    void setMouseHandle(Mouse* mouse);
    void setCameraUpdateCallback(std::function<void(float, float,bool)>&& cameraUpdateCallback);

protected:
    void handle() override;

private:
    Mouse* mMouse;
    double mXPos;
    double mYPos;

    std::function<void(float, float,bool)> mCameraUpdateCallback;
};
#endif  // !OPENGL_PBR_EVENT_MOVE_EVENTS_HXX