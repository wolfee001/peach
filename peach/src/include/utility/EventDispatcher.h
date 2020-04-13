#pragma once

#include <utility/Event.h>

namespace peach {

class EventDispatcher {
    template <typename T> using EventFn = std::function<bool(T&)>;

public:
    explicit EventDispatcher(Event& event)
        : mEvent(event)
    {
    }

    template <typename T> bool Dispatch(EventFn<T> func)
    {
        if (mEvent.GetEventType() == T::GetStaticType()) {
            mEvent.mHandled = func(*static_cast<T*>(&mEvent));
            return true;
        }
        return false;
    }

private:
    Event& mEvent;
};

}