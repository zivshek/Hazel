#include "pch.h"
#include "Application.h"

#include "Hazel/Events/MouseEvents.h"

#include <glad/glad.h>
#include "Hazel/Renderer/Buffers.h"
#include "Hazel/Renderer/Renderer.h"

#include "InputCodes.h"

namespace Hazel
{
#define BIND(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
        : m_Running{ true }
        , m_LayerStack{}
        , m_ImGuiLayer{ new ImGuiLayer() }
        , m_Window{ std::move(Window::Create()) }
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exits");
        s_Instance = this;

        m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });

        PushOverlay(m_ImGuiLayer);
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

            for (Layer* layer : m_LayerStack)
                layer->OnDraw();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->OnDrawImGui();
            m_ImGuiLayer->End();

            m_Window->OnUpdate();
        }
    }

    void Application::OnEvent(Event& e)
    {
        EventDispatcher dispatcher{ e };
        dispatcher.Dispatch<WindowCloseEvent>(BIND(OnWindowClose));

        float speed = 10.0f;
        float delta = 1.0f / 60.0f;
        float x = 0; float y = 0;
        dispatcher.Dispatch<KeyPressedEvent>([speed, delta, &x, &y](KeyPressedEvent& event) -> bool
            {
                switch (event.GetKeyCode())
                {
                case HZ_KEY_W:
                    y += speed * delta;
                    return true;
                case HZ_KEY_S:
                    y -= speed * delta;
                    return true;
                case HZ_KEY_A:
                    x -= speed * delta;
                    return true;
                case HZ_KEY_D:
                    x += speed * delta;
                    return true;
                }
                return false;
            });
        m_OrthoCamera.SetPosition(m_OrthoCamera.GetPosition() + glm::vec3(x, y, 0));

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