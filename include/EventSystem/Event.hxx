#ifndef OPENGL_PBR_EVENT_HXX
#define OPENGL_PBR_EVENT_HXX

#include <array>
#include <functional>

#include "Keyboard.hxx"
#include "Mouse.hxx"

enum class EventCategory
{
    KEYBOARD,
    MOUSE,
    CAMERA,
};

class Window;
class Event
{
    friend class EventDispatcher;

public:
    virtual EventCategory category() = 0;
    virtual ~Event(){};

    virtual std::string toString() = 0;

protected:
    virtual void handle() = 0;
};

class KeyboardEvent : public Event
{
public:
    KeyboardEvent(int key, Keyboard* keyboard, Window* window, Mouse* mouse);
    std::string toString() override;

    EventCategory category() override
    {
        return EventCategory::KEYBOARD;
    }

    void setKeyboardHandle(Keyboard* keyboard);
    void setMouseHandle(Mouse* mouse);

protected:
    void handle() override{};

    int       mKey;
    Keyboard* mKeyboard;
    Window*   mWindow;
    Mouse*    mMouse;
};

class KeyboardPressEvent : public KeyboardEvent
{
public:
    using KeyboardEvent::KeyboardEvent;

protected:
    void handle() override;
};

class KeyboardReleaseEvent : public KeyboardEvent
{
public:
    using KeyboardEvent::KeyboardEvent;
    std::string toString() override;

protected:
    void handle() override;
};

#endif  // OPENGL_PBR_EVENT_HXX