#pragma once

#include "Core.h"
#include "Window.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvents.h"

namespace Hazel
{
    class HAZEL_API Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);
    private:
        std::unique_ptr<Window> m_Window;
        bool m_Running;
        LayerStack m_LayerStack;
    };

    Application* CreateApplication();
}