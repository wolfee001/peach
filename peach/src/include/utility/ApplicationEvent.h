#pragma once

#include <utility/Event.h>

namespace peach {

class WindowResizedEvent : public Event {
public:
    WindowResizedEvent(const unsigned int width, const unsigned int height, const float scaling)
        : mWidth(width)
        , mHeight(height)
        , mFrameBufferScaling(scaling)
    {
    }

    unsigned int GetWidth() const { return mWidth; }
    unsigned int GetHeight() const { return mHeight; }
    float GetFrameBufferScaling() const { return mFrameBufferScaling; }

    EVENT_CLASS_TYPE(WindowResize)

private:
    unsigned int mWidth = 0;
    unsigned int mHeight = 0;
    float mFrameBufferScaling = 1.f;
};

class WindowCloseEvent final : public Event {
public:
    EVENT_CLASS_TYPE(WindowClose)
};

}