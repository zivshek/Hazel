#include "pch.h"
#include "Application.h"

#include "Hazel/Renderer/Renderer.h"
#include <glfw/glfw3.h>

namespace Hazel
{
#define BIND(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
        : m_Running{ true }
        , m_LayerStack{}
        , m_ImGuiLayer{ new ImGuiLayer() }
        , m_Window{ std::move(Window::Create()) }
        , m_LastFrameTime{ 0 }
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exits");
        s_Instance = this;

        m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });
        m_Window->SetVSync(true);

        Renderer::Init();

        PushOverlay(m_ImGuiLayer);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            float time = (float)glfwGetTime();
            Timestep deltaTime = time - m_LastFrameTime;
            m_LastFrameTime = time;

            for (auto layer : m_LayerStack)
                layer->OnUpdate(deltaTime);

            for (auto layer : m_LayerStack)
                layer->OnDraw();

            m_ImGuiLayer->Begin();
            for (auto layer : m_LayerStack)
                layer->OnDrawImGui();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher{ e };
        dispatcher.Dispatch<WindowCloseEvent>(BIND(OnWindowClose));

        for (auto it = m_LayerStack.end(); it != m_LayerStack.begin();)
        {
            (*--it)->OnEvent(e);
            if (e.Handled())
                break;
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& e)
    {
        m_Running = false;
        return true;
    }

    void Application::PushLayer(Layer* layer)
    {
        m_LayerStack.Push(layer);
        layer->OnAttach();
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
        layer->OnAttach();
    }
}