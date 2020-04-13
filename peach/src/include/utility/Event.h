#pragma once

namespace peach {

#define EVENT_CLASS_TYPE(type)                                                                                                                                 \
    static EventType GetStaticType() { return EventType::type; }                                                                                               \
    virtual EventType GetEventType() const override { return GetStaticType(); }

class Event {
    friend class EventDispatcher;

protected:
    enum class EventType {
        WindowClose,
        WindowResize,
        WindowFocus,
        WindowLostFocus,
        WindowMoved,

        KeyPressed,
        KeyReleased,
        KeyTyped,

        MouseButtonPressed,
        MouseButtonReleased,
        MouseMoved,
        MouseScrolled
    };

public:
    virtual ~Event() = default;

    virtual EventType GetEventType() const = 0;

    bool Handled() const { return mHandled; }

protected:
    bool mHandled = false;
};

}