#pragma once

#include "Core.h"
#include "Window.h"
#include "Input.h"
#include "Hazel/LayerStack.h"
#include "Hazel/Events/Event.h"
#include "Hazel/Events/ApplicationEvents.h"

#include "Hazel/ImGui/ImGuiLayer.h"
#include "Hazel/Renderer/ShaderProgram.h"
#include "Hazel/Renderer/Buffers.h"

namespace Hazel
{
    class  Application
    {
    public:
        Application();
        virtual ~Application();
        void Run();

        void OnEvent(Event& e);

        void PushLayer(Layer* layer);
        void PushOverlay(Layer* layer);

        inline static Application& Get() { return *s_Instance; }
        inline Window& GetWindow() { return *m_Window; }
    private:
        bool OnWindowClose(WindowCloseEvent& e);

        std::unique_ptr<Window> m_Window;
        ImGuiLayer* m_ImGuiLayer;
        bool m_Running;
        LayerStack m_LayerStack;

        uint m_VertexArray;
        std::unique_ptr<ShaderProgram> m_ShaderProgram;
        std::unique_ptr<VertexBuffer> m_VertexBuffer;
        std::unique_ptr<IndexBuffer> m_IndexBuffer;

        static Application* s_Instance;
    };

    Application* CreateApplication();
}