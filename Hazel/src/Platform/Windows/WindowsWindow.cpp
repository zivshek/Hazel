#include "pch.h"
#include "WindowsWindow.h"

namespace Hazel
{
    static bool s_GLFWInitialized = false;

    std::unique_ptr<Window> Window::Create(const WindowProps& props)
    {
        return std::make_unique<WindowsWindow>(props);
    }

    WindowsWindow::WindowsWindow(const WindowProps& props)
        : m_WindowData {}
        , m_GLFWWindow {nullptr}
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
        glfwSwapBuffers(m_GLFWWindow);
    }

    void WindowsWindow::SetVSync(bool enabled)
    {
        glfwSwapInterval(enabled ? 1 : 0);
        m_WindowData.VSync = enabled;
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
        glfwMakeContextCurrent(m_GLFWWindow);
        glfwSetWindowUserPointer(m_GLFWWindow, &m_WindowData);
        SetVSync(true);
    }

    void WindowsWindow::Shutdown()
    {
        glfwDestroyWindow(m_GLFWWindow);
    }
}
