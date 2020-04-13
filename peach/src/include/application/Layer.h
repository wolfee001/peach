#pragma once

namespace peach {

class TimeSpan;
class Event;

class Layer {
public:
    virtual void OnLogic(const TimeSpan& /* timeStep */) {}
    virtual void OnRender() {}
    virtual void OnGui() {}

    virtual void OnEvent(Event& /* event */) {}

    virtual ~Layer() = default;
};

} // namespace peach