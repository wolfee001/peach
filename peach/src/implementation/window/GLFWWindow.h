#pragma once

#include <window/Window.h>

struct GLFWwindow;

namespace peach {

class GLFWWindow : public Window {
public:
    struct WindowProps {
        std::string mTitle;
        unsigned int mWidth = 0;
        unsigned int mHeight = 0;
        float mFrameBufferScaling = 0.F;
    };

public:
    GLFWWindow(unsigned int width, unsigned int height, const std::string& title);

    virtual void Update() const override;
    virtual unsigned int GetWidth() const override;
    virtual unsigned int GetHeight() const override;
    virtual float GetFrameBufferScaling() const override;
    virtual void* GetUnderlyingWindow() const override;

    virtual void RegisterEventCallback(const EventCallback& callback) override;

    ~GLFWWindow();

private:
    void RegisterNativeCallbacks();

private:
    GLFWwindow* mWindow;
    WindowProps mWindowProps;
    EventCallback mEventCallback;
};

} // namespace peach