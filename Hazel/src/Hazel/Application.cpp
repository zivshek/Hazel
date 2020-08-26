#include "pch.h"
#include "Application.h"

#include "Hazel/Events/MouseEvents.h"

#include <glad/glad.h>

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

        //m_Window->SetEventCallback(BIND(OnEvent));
        m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });

        PushOverlay(m_ImGuiLayer);

        glGenVertexArrays(1, &m_VertexArray);
        glBindVertexArray(m_VertexArray);

        glGenBuffers(1, &m_VertexBuffer);
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBuffer);

        float vertices[9] = {
            0.0f, 0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            -0.5f, -0.5f, 0.0f
        };

        glBufferData(GL_ARRAY_BUFFER, sizeof vertices, vertices, GL_STATIC_DRAW);

        glEnableVertexAttribArray(0);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), nullptr);

        glGenBuffers(1, &m_IndexBuffer);
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBuffer);

        uint indices[3] = { 0, 2, 1 };
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof indices, indices, GL_STATIC_DRAW);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            out vec3 v_Position;

            void main()
            {
                v_Position = a_Position;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec3 v_Position;

            void main()
            {
                color = vec4(v_Position, 1.0);
            }
        )";
        m_ShaderProgram = std::make_unique<ShaderProgram>(vertexSrc, fragSrc);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            glClearColor(0, 0.2f, 0.3f, 1);
            glClear(GL_COLOR_BUFFER_BIT);

            m_ShaderProgram->Bind();

            glBindVertexArray(m_VertexArray);
            glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, nullptr);

            for (auto layer : m_LayerStack)
                layer->OnUpdate();

            m_ImGuiLayer->Begin();
            for (Layer* layer : m_LayerStack)
                layer->DrawImGui();
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