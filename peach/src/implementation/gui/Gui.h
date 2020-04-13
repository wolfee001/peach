#pragma once

namespace peach {

class Window;

class Gui {
public:
    explicit Gui(const Window& window);
    ~Gui();

    static void Begin();
    void End();

private:
    const Window& mWindow;
};

} // namespace peach
