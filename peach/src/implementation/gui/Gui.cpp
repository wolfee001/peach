#include "Gui.h"

#include <window/Window.h>

#include <imgui_binding/ImGuiGLFW.h>
#include <imgui_binding/ImGuiOpenGL.h>

namespace peach {

Gui::Gui(const Window& window)
    : mWindow(window)
{
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    unsigned int flags = ImGuiConfigFlags_NavEnableKeyboard;
    flags |= ImGuiConfigFlags_DockingEnable;
    flags |= ImGuiConfigFlags_ViewportsEnable;
    io.ConfigFlags = static_cast<int>(flags);

    ImGui::StyleColorsDark();

    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 0.F;
    style.Colors[ImGuiCol_WindowBg].w = 1.F;

    ImGui_ImplGlfw_InitForOpenGL(static_cast<GLFWwindow*>(mWindow.GetUnderlyingWindow()), true);
    ImGui_ImplOpenGL3_Init("#version 410 core");
}

Gui::~Gui()
{
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
}

void Gui::Begin()
{
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();
}

void Gui::End()
{
    ImGuiIO& io = ImGui::GetIO();
    io.DisplaySize = ImVec2(static_cast<float>(mWindow.GetWidth()), static_cast<float>(mWindow.GetHeight()));
    io.DisplayFramebufferScale = ImVec2(mWindow.GetFrameBufferScaling(), mWindow.GetFrameBufferScaling());

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    ImGui::UpdatePlatformWindows();
    ImGui::RenderPlatformWindowsDefault();
}

} // namespace peach