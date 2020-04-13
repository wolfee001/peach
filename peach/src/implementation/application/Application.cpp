#include <application/Application.h>
#include <application/Layer.h>
#include <gui/Gui.h>
#include <utility/ApplicationEvent.h>
#include <utility/Assert.h>
#include <utility/EventDispatcher.h>
#include <utility/TimeSpan.h>
#include <window/Window.h>

#include <glad/glad.h>
#include <imgui.h>

namespace peach {

Application::Application() = default;

void Application::CreateWindow(unsigned int width /* = 1280 */, unsigned int height /* = 720 */, const std::string& name /* = "peach engine" */)
{
    Assert(!mWindow, "Application window already exists!");
    mWindow = Window::Create(width, height, name);
    mWindow->RegisterEventCallback([this](Event& event) { OnEvent(event); });
}

void Application::CreateGui()
{
    Assert(mWindow, "Window is a must for GUI");
    mGui = std::make_unique<Gui>(*mWindow);
}

void Application::Run()
{
    mTimer.Reset();

    while (mRunning) {
        const TimeSpan ts = mTimer.Tick();

        for (auto& layer : mAttachedLayers) {
            layer->OnLogic(ts);
        }

        if (mWindow) {
            for (auto& layer : mAttachedLayers) {
                layer->OnRender();
            }

            if (mGui) {
                for (auto& layer : mAttachedLayers) {
                    mGui->Begin();
                    layer->OnGui();
                    mGui->End();
                }
            }

            mWindow->Update();
        }
    }
}

void Application::AddLayer(Layer& layer) { mAttachedLayers.push_back(&layer); }

void Application::RemoveLayer(Layer& layer)
{
    mAttachedLayers.erase(
        std::remove_if(mAttachedLayers.begin(), mAttachedLayers.end(), [&layer](const auto& element) { return element == &layer; }), mAttachedLayers.end());
}

Application::~Application() = default;

void Application::OnEvent(Event& event)
{
    EventDispatcher dispatcher(event);
    dispatcher.Dispatch<WindowCloseEvent>([&](WindowCloseEvent & /* unused */) -> bool {
        mRunning = false;
        return false;
    });
}

} // namespace peach