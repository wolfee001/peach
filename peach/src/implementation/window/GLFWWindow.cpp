#include "GLFWWindow.h"

#include <glad/glad.h>

#include <GLFW/glfw3.h>

#include <utility/ApplicationEvent.h>
#include <utility/Assert.h>
#include <utility/KeyEvent.h>
#include <utility/MouseEvent.h>

#include <memory>

namespace peach {

static void __GladCallbackEmptyFunction(const char* /* unused */, void* /* unused */, int /* unused */, ...) {} // NOLINT(cert-dcl50-cpp)

GLFWWindow::GLFWWindow(unsigned int width, unsigned int height, const std::string& title)
{
    int glfwSuccess = glfwInit();
    Assert(glfwSuccess == GLFW_TRUE, "Could not initialize GLFW! Error code: {}", glfwSuccess);
    glfwSetErrorCallback([](int code, const char* message) { Assert(false, "GLFW error! {}: {}", code, message); });

#ifdef __APPLE__
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
#endif

    mWindow = glfwCreateWindow(static_cast<int>(width), static_cast<int>(height), title.c_str(), nullptr, nullptr);

    if (mWindow == nullptr) {
        Assert(false, "Unable to create GLFW window!");
        glfwTerminate();
        return;
    }

    mWindowProps.mTitle = title;
    mWindowProps.mWidth = width;
    mWindowProps.mHeight = height;
    glfwGetWindowContentScale(mWindow, &(mWindowProps.mFrameBufferScaling), nullptr);

    glfwMakeContextCurrent(mWindow);
    glfwSetWindowUserPointer(mWindow, this);

    RegisterNativeCallbacks();

    glfwSwapInterval(1);

    int gladSuccess = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress)); // NOLINT(cppcoreguidelines-pro-type-reinterpret-cast)
    Assert(gladSuccess, "Could not initialize Glad! Error code: {}", gladSuccess);

    glad_set_pre_callback(__GladCallbackEmptyFunction);
    glad_set_post_callback(__GladCallbackEmptyFunction);

    auto& logger = LogManager::GetInstance().GetLogger("peach");
    logger.Info("OpenGL {:10} {}", "vendor:", glGetString(GL_VENDOR));
    logger.Info("OpenGL {:10} {}", "renderer:", glGetString(GL_RENDERER));
    logger.Info("OpenGL {:10} {}", "version:", glGetString(GL_VERSION));
}

void GLFWWindow::Update() const
{
    glfwMakeContextCurrent(mWindow);
    glfwSwapBuffers(mWindow);
    glfwPollEvents();
}

unsigned int GLFWWindow::GetWidth() const { return mWindowProps.mWidth; }

unsigned int GLFWWindow::GetHeight() const { return mWindowProps.mHeight; }

float GLFWWindow::GetFrameBufferScaling() const { return mWindowProps.mFrameBufferScaling; }

void* GLFWWindow::GetUnderlyingWindow() const { return static_cast<void*>(mWindow); }

void GLFWWindow::RegisterEventCallback(const EventCallback& callback) { mEventCallback = callback; }

GLFWWindow::~GLFWWindow()
{
    glfwDestroyWindow(mWindow);
    mWindow = nullptr;
    glfwTerminate();
}

void GLFWWindow::RegisterNativeCallbacks()
{
    glfwSetWindowSizeCallback(mWindow, [](GLFWwindow* window, int width, int height) {
        auto* abstractWindow = static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window));
        WindowProps& props = abstractWindow->mWindowProps;
        props.mWidth = static_cast<unsigned int>(width);
        props.mHeight = static_cast<unsigned int>(height);
        glfwGetWindowContentScale(window, &(props.mFrameBufferScaling), nullptr);
        WindowResizedEvent event(props.mWidth, props.mHeight, props.mFrameBufferScaling);
        abstractWindow->mEventCallback(event);
    });

    glfwSetWindowCloseCallback(mWindow, [](GLFWwindow* window) {
        WindowCloseEvent event;
        static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
    });

    glfwSetKeyCallback(mWindow, [](GLFWwindow* window, int key, int /*scancode*/, int action, int /*mods*/) {
        switch (action) {
        case GLFW_PRESS: {
            KeyPressedEvent event(static_cast<uint8_t>(key), 0);
            static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            KeyReleasedEvent event(static_cast<uint8_t>(key));
            static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
            break;
        }
        case GLFW_REPEAT: {
            KeyPressedEvent event(static_cast<uint8_t>(key), 1);
            static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetCharCallback(mWindow, [](GLFWwindow* window, unsigned int keyCode) {
        KeyTypedEvent event(keyCode);
        static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
    });

    glfwSetMouseButtonCallback(mWindow, [](GLFWwindow* window, int button, int action, int /*mods*/) {
        switch (action) {
        case GLFW_PRESS: {
            MouseButtonPressedEvent event(static_cast<uint8_t>(button));
            static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
            break;
        }
        case GLFW_RELEASE: {
            MouseButtonReleasedEvent event(static_cast<uint8_t>(button));
            static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
            break;
        }
        default:
            break;
        }
    });

    glfwSetScrollCallback(mWindow, [](GLFWwindow* window, double xOffset, double yOffset) {
        MouseScrolledEvent event(static_cast<float>(xOffset), static_cast<float>(yOffset));
        static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
    });

    glfwSetCursorPosCallback(mWindow, [](GLFWwindow* window, double xPos, double yPos) {
        MouseMovedEvent event(static_cast<float>(xPos), static_cast<float>(yPos));
        static_cast<GLFWWindow*>(glfwGetWindowUserPointer(window))->mEventCallback(event);
    });
}

/* static */ std::unique_ptr<Window> Window::Create(unsigned int width, unsigned int height, const std::string& title)
{
    return std::make_unique<GLFWWindow>(width, height, title);
}

} // namespace peach