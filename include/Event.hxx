#ifndef OPENGL_PBR_EVENT_HXX
#define OPENGL_PBR_EVENT_HXX

#include <array>
#include <functional>

#include "Keyboard.hxx"
#include "Mouse.hxx"

class Window;
class Event
{
    friend class EventDispatcher;

public:
    virtual ~Event(){};

protected:
    virtual void handle() = 0;
};

class KeyboardEvent : public Event
{
public:
    KeyboardEvent(int action, int key, Keyboard& keyboard, Window& window);

protected:
    void handle() override;

private:
    int       mAction, mKey;
    Keyboard& mKeyboard;
    Window&   mWindow;
};

class MouseMoveEvent : public Event
{
public:
    MouseMoveEvent(Mouse& mouse, double xPos, double yPos);

protected:
    void handle() override;

private:
    Mouse& mMouse;
    double mXPos;
    double mYPos;
};

class EventDispatcher
{
public:
    EventDispatcher(Keyboard& keyboard, Mouse& mouse)  //
        : mKeyboard{ keyboard }
        , mMouse{ mouse }
    {
    }

    Keyboard& getKeyboard()
    {
        return mKeyboard;
    }

    Mouse& getMouse()
    {
        return mMouse;
    }

    void dispatch(Event& event)
    {
        event.handle();
    }

private:
    Keyboard& mKeyboard;
    Mouse&    mMouse;
};

#endif  // OPENGL_PBR_EVENT_HXX