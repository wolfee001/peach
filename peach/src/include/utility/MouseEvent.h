#pragma once

#include <utility/Event.h>

namespace peach {

class MouseMovedEvent : public Event {
public:
    MouseMovedEvent(const float x, const float y)
        : mMouseX(x)
        , mMouseY(y)
    {
    }

    float GetX() const { return mMouseX; }
    float GetY() const { return mMouseY; }

    EVENT_CLASS_TYPE(MouseMoved)

private:
    float mMouseX = 0.f;
    float mMouseY = 0.f;
};

class MouseScrolledEvent : public Event {
public:
    MouseScrolledEvent(const float x, const float y)
        : mXOffset(x)
        , mYOffset(y)
    {
    }

    float GetXOffset() const { return mXOffset; }
    float GetYOffset() const { return mYOffset; }

    EVENT_CLASS_TYPE(MouseScrolled)

private:
    float mXOffset = 0.f;
    float mYOffset = 0.f;
};

class MouseButtonEvent : public Event {
public:
    virtual ~MouseButtonEvent() = default;

    uint8_t GetButton() const { return mButton; }

protected:
    explicit MouseButtonEvent(const uint8_t button)
        : mButton(button)
    {
    }

protected:
    uint8_t mButton = 0;
};

class MouseButtonPressedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonPressedEvent(const uint8_t button)
        : MouseButtonEvent(button)
    {
    }

    EVENT_CLASS_TYPE(MouseButtonPressed)
};

class MouseButtonReleasedEvent : public MouseButtonEvent {
public:
    explicit MouseButtonReleasedEvent(const uint8_t button)
        : MouseButtonEvent(button)
    {
    }

    EVENT_CLASS_TYPE(MouseButtonReleased)
};

}