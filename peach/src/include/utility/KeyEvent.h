#pragma once

#include <utility/Event.h>

namespace peach {

class KeyEvent : public Event {
public:
    virtual ~KeyEvent() = default;

    unsigned int GetKeyCode() const { return mKeyCode; }

protected:
    explicit KeyEvent(const unsigned int keyCode)
        : mKeyCode(keyCode)
    {
    }

protected:
    unsigned int mKeyCode;
};

class KeyPressedEvent : public KeyEvent {
public:
    KeyPressedEvent(const unsigned int keyCode, const size_t repeatCount)
        : KeyEvent(keyCode)
        , mRepeatCount(repeatCount)
    {
    }

    inline size_t GetRepeatCount() const { return mRepeatCount; }

    EVENT_CLASS_TYPE(KeyPressed)

private:
    size_t mRepeatCount = 0;
};

class KeyReleasedEvent : public KeyEvent {
public:
    explicit KeyReleasedEvent(const unsigned int keyCode)
        : KeyEvent(keyCode)
    {
    }

    EVENT_CLASS_TYPE(KeyReleased)
};

class KeyTypedEvent : public KeyEvent {
public:
    explicit KeyTypedEvent(const unsigned int keyCode)
        : KeyEvent(keyCode)
    {
    }

    EVENT_CLASS_TYPE(KeyTyped)
};

}