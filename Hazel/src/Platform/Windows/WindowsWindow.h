#pragma once

#include "pch.h"

#include "Hazel/Window.h"
#include <GLFW/glfw3.h>

namespace Hazel
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowProps& props);
        ~WindowsWindow();

        void OnUpdate() override;
        inline uint GetWidth() const override { return m_WindowData.Width; }
        inline uint GetHeight() const override { return m_WindowData.Height; }
        inline void SetEventCallback(const EventCallback& callback) override { m_WindowData.EventCallback = callback; }
        void SetVSync(bool enabled) override;
        inline bool IsVSync() const override { return m_WindowData.VSync; }

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_GLFWWindow;

        struct WindowData
        {
            std::string Title;
            uint Width, Height;
            bool VSync;

            EventCallback EventCallback;
        } m_WindowData;
    };
}

