#pragma once

#include <chrono>
#include <memory>
#include <string>
#include <vector>

#include <utility/Timer.h>

namespace peach {

class Gui;
class Window;
class Layer;
class Event;

class Application final {
public:
    Application();

    void CreateWindow(unsigned int width = 1280, unsigned int height = 720, const std::string& name = "peach engine");
    void CreateGui();

    void Run();

    void AddLayer(Layer& layer);
    void RemoveLayer(Layer& layer);

    ~Application();

private:
    void OnEvent(Event& event);

private:
    std::unique_ptr<Window> mWindow { nullptr };
    std::unique_ptr<Gui> mGui { nullptr };
    bool mRunning = true;
    Timer mTimer;
    std::vector<Layer*> mAttachedLayers;
};

} // namespace peach