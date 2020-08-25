#include "pch.h"
#include "WindowsWindow.h"

#include "Hazel/Events/ApplicationEvents.h"
#include "Hazel/Events/MouseEvents.h"
#include "Hazel/Events/KeyEvents.h"

#include "Platform/OpenGL/OpenGLContext.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
    static bool s_GLFWInitialized = false;

    std::unique_ptr<Window> Window::Create(const WindowProps& props)
    {
        return std::make_unique<WindowsWindow>(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
        : m_WindowData{}
        , m_GLFWWindow{ nullptr }
        , m_GraphicsContext{ nullptr }
    {
        Init(props);
    }

    WindowsWindow::~WindowsWindow()
    {
        Shutdown();
    }

    void WindowsWindow::OnUpdate()
    {
        glfwPollEvents();
        if (m_GraphicsContext)
            m_GraphicsContext->SwapBuffers();
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        m_WindowData.VSync = enabled;
    }

    void* WindowsWindow::GetNativeWindow() const
    {
        return m_GLFWWindow;
    }

    void WindowsWindow::Init(const WindowProps& props)
    {
        m_WindowData.Title = props.Title;
        m_WindowData.Width = props.Width;
        m_WindowData.Height = props.Height;

        if (!s_GLFWInitialized)
        {
            const int success = glfwInit();
            HZ_CORE_ASSERT(success, "GLFW Initializing failed");
            HZ_CORE_INFO("GLFW Initialized");
            s_GLFWInitialized = true;
        }

        m_GLFWWindow = glfwCreateWindow(props.Width, props.Height, props.Title.c_str(), nullptr, nullptr);
        HZ_CORE_INFO("GLFW window \"{0}\" created, width: {1}, height: {2}", props.Title, props.Width, props.Height);

        m_GraphicsContext = std::make_unique<OpenGLContext>(m_GLFWWindow);
        m_GraphicsContext->Init();

        glfwSetWindowUserPointer(m_GLFWWindow, &m_WindowData);
        SetVSync(true);

        // GLFW callbacks
        glfwSetWindowSizeCallback(m_GLFWWindow, OnWindowSizeCallback);
        glfwSetWindowCloseCallback(m_GLFWWindow, OnWindowCloseCallback);
        glfwSetKeyCallback(m_GLFWWindow, OnKeyEventCallback);
        glfwSetCharCallback(m_GLFWWindow, OnCharEventCallback);
        glfwSetMouseButtonCallback(m_GLFWWindow, OnMouseButtonCallback);
        glfwSetScrollCallback(m_GLFWWindow, OnMouseScrollCallback);
        glfwSetCursorPosCallback(m_GLFWWindow, OnCursorPosCallback);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_GLFWWindow);
    }

    // static callbacks
    void WindowsWindow::OnWindowSizeCallback(GLFWwindow* window, int width, int height)
    {
        auto windowData = GetWindowDataPtr(window);
        windowData->Width = static_cast<uint>(width);
        windowData->Height = static_cast<uint>(height);

        windowData->EventCallback(WindowResizeEvent{ windowData->Width, windowData->Height });
    }

    void WindowsWindow::OnWindowCloseCallback(GLFWwindow* window)
    {
        auto windowData = GetWindowDataPtr(window);
        windowData->EventCallback(WindowCloseEvent{});
    }

    void WindowsWindow::OnKeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
    {
        auto windowData = GetWindowDataPtr(window);

        switch (action)
        {
        case GLFW_PRESS:
            windowData->EventCallback(KeyPressedEvent{ key, 0 });
            break;
        case GLFW_RELEASE:
            windowData->EventCallback(KeyReleasedEvent{ key });
            break;
        case GLFW_REPEAT:
            windowData->EventCallback(KeyPressedEvent{ key, 1 });
            break;
        }
    }

    void WindowsWindow::OnCharEventCallback(GLFWwindow* window, uint character)
    {
        auto windowData = GetWindowDataPtr(window);
        windowData->EventCallback(KeyTypedEvent{ (int)character });
    }

    void WindowsWindow::OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
    {
        auto windowData = GetWindowDataPtr(window);

        switch (action)
        {
        case GLFW_PRESS:
            windowData->EventCallback(MousePressedEvent{ button });
            break;
        case GLFW_RELEASE:
            windowData->EventCallback(MouseReleasedEvent{ button });
            break;
        }
    }

    void WindowsWindow::OnMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
    {
        auto windowData = GetWindowDataPtr(window);
        windowData->EventCallback(MouseScrolledEvent{ static_cast<float>(xOffset), static_cast<float>(yOffset) });
    }

    void WindowsWindow::OnCursorPosCallback(GLFWwindow* window, double x, double y)
    {
        auto windowData = GetWindowDataPtr(window);
        windowData->EventCallback(MouseMovedEvent{ static_cast<float>(x), static_cast<float>(y) });
    }

    Hazel::WindowsWindow::WindowData* WindowsWindow::GetWindowDataPtr(GLFWwindow* window)
    {
        return (WindowData*)glfwGetWindowUserPointer(window);
    }
}