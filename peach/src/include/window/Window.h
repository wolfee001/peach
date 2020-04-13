#pragma once

#include <memory>
#include <string>

namespace peach {

class Event;
class Window;

class Window {
    friend class Application;

public:
    using EventCallback = std::function<void(Event&)>;

public:
    virtual void Update() const = 0;
    virtual unsigned int GetWidth() const = 0;
    virtual unsigned int GetHeight() const = 0;
    virtual float GetFrameBufferScaling() const = 0;
    virtual void* GetUnderlyingWindow() const = 0;

    virtual void RegisterEventCallback(const EventCallback& callback) = 0;

    virtual ~Window() = default;

protected:
    static std::unique_ptr<Window> Create(unsigned int width = 1280, unsigned int height = 720, const std::string& title = "Peach Engine");

    Window() = default;
};

} // namespace peach