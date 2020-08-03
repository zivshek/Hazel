#include "pch.h"
#include "Application.h"

#include "Hazel/Events/MouseEvents.h"

namespace Hazel
{
    Application::Application()
        : m_Running{ true }
    {
        m_Window = std::move(Window::Create());
        //m_Window->SetEventCallback(std::bind(&Application::OnEvent, this, std::placeholders::_1));
        m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        HZ_CORE_INFO(e);
    }
}