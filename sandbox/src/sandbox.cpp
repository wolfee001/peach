#include <peach/Peach.h>

class Alma : peach::GuiElement {
public:
    void DrawGui() override
    {
        AddGuiElement(f1);
        AddGuiElement(i1);
    }

private:
    float f1 = 0.F;
    int i1 = 0;
};

class Banan : peach::GuiElement {
public:
    void DrawGui() override { AddGuiElement(almak); }

private:
    static constexpr size_t almak_szama = 5;
    std::vector<Alma> almak = std::vector<Alma>(almak_szama);
};

class SandboxLayer : public peach::Layer {
public:
    void OnRender() override
    {
        glClearColor(0.F, 0.F, 1.F, 0.F);
        glClear(GL_COLOR_BUFFER_BIT);
    }

    void OnGui() override
    {
        ImGui::Begin("Demo window");
        AddGuiElement(alma);
        AddGuiElement(banan);
        ImGui::End();
    }

private:
    Alma alma;
    Banan banan;
};

int main(int /*argc*/, char** /*argv*/)
{
    std::unique_ptr app = std::make_unique<peach::Application>();
    app->CreateWindow();
    app->CreateGui();
    SandboxLayer layer;
    app->AddLayer(layer);
    app->Run();
    app->RemoveLayer(layer);
    return 0;
}