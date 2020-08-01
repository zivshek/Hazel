#include "pch.h"
#include "Application.h"

#include "Hazel/Events/MouseEvents.h"

namespace Hazel
{
    Application::Application()
        : m_Window{std::move(Window::Create())}
        , m_Running{true}
    {
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
}