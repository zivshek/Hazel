#pragma once

#include "pch.h"

#include "Hazel/Core/Window.h"

struct GLFWwindow;

namespace Hazel
{
    class GraphicsContext;
}

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
        void* GetNativeWindow() const override;

    private:
        virtual void Init(const WindowProps& props);
        virtual void Shutdown();

        GLFWwindow* m_GLFWWindow;
        std::unique_ptr<GraphicsContext> m_GraphicsContext;

        struct WindowData
        {
            std::string Title;
            uint Width, Height;
            bool VSync;

            EventCallback EventCallback;
        } m_WindowData;

        static void OnWindowSizeCallback(GLFWwindow* window, int width, int height);
        static void OnWindowCloseCallback(GLFWwindow* window);
        static void OnKeyEventCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
        static void OnCharEventCallback(GLFWwindow* window, uint character);
        static void OnMouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
        static void OnMouseScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
        static void OnCursorPosCallback(GLFWwindow* window, double x, double y);
        static WindowData* GetWindowDataPtr(GLFWwindow* window);
    };
}
