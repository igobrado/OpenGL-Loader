#ifndef OPENGL_PBR_EVENT_DISPATCHER_HXX
#define OPENGL_PBR_EVENT_DISPATCHER_HXX

#include "Event.hxx"
#include "common/Logging.hxx"

class EventDispatcher
{
public:
    EventDispatcher(Keyboard& keyboard, Mouse& mouse)  //
        : mKeyboard{ keyboard }
        , mMouse{ mouse }
    {
    }

    void dispatch(Event& event)
    {
        OGL_CORE_INFO(std::string{ "Dispatching " + event.toString() });
        event.handle();
    }

private:
    Keyboard& mKeyboard;
    Mouse&    mMouse;
};

#endif  // !OPENGL_PBR_EVENT_DISPATCHER_HXX