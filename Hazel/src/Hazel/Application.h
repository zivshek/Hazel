#pragma once

#include "Core.h"
#include "Window.h"
#include "Input.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvents.h"

#include "Hazel/ImGui/ImGuiLayer.h"

namespace Hazel
{
    class  Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event& e);
        bool OnWindowClose(WindowCloseEvent& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running;
        LayerStack m_LayerStack;

        static Application* s_Instance;
    };

    Application* CreateApplication();
}