#include "pch.h"
#include "Application.h"

#include "Hazel/Events/MouseEvents.h"

namespace Hazel
{
#define BIND(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application::Application()
        : m_Running{ true }
        , m_LayerStack{}
    {
        m_Window = std::move(Window::Create());
        //m_Window->SetEventCallback(BIND(OnEvent));
        m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            for (auto layer : m_LayerStack)
                layer->OnUpdate();

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
    }

    void Application::PushOverlay(Layer* layer)
    {
        m_LayerStack.PushOverlay(layer);
    }

}