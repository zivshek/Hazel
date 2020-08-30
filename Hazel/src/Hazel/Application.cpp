#include "pch.h"
#include "Application.h"

#include "Hazel/Events/MouseEvents.h"

#include <glad/glad.h>
#include "Hazel/Renderer/Buffers.h"
#include "Hazel/Renderer/Renderer.h"

namespace Hazel
{
#define BIND(x) std::bind(&Application::x, this, std::placeholders::_1)

    Application* Application::s_Instance = nullptr;

    Application::Application()
        : m_Running{ true }
        , m_LayerStack{}
        , m_ImGuiLayer{ new ImGuiLayer() }
        , m_Window{ std::move(Window::Create()) }
        , m_VertexArray{ VertexArray::Create() }
    {
        HZ_CORE_ASSERT(!s_Instance, "Application already exits");
        s_Instance = this;

        m_Window->SetEventCallback([this](Event& e) { OnEvent(e); });

        PushOverlay(m_ImGuiLayer);

        float vertices[3 * 7] = {
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };
        uint indices[3] = { 0, 2, 1 };

        auto vertexBuffer = VertexBuffer::Create(vertices, sizeof vertices);
        vertexBuffer->SetLayout(
            {
                { ShaderDataType::Float3, "a_Position" },
                { ShaderDataType::Float4, "a_Color"}
            });
        auto indexBuffer = IndexBuffer::Create(indices, sizeof(indices) / sizeof(float));

        m_VertexArray->AddVertexBuffer(vertexBuffer);
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;
            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = vec4(a_Position, 1.0);
            }
        )";

        std::string fragSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec4 v_Color;

            void main()
            {
                color = v_Color;
            }
        )";
        m_ShaderProgram = std::make_shared<ShaderProgram>(vertexSrc, fragSrc);
    }

    Application::~Application()
    {
    }

    void Application::Run()
    {
        while (m_Running)
        {
            RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
            RenderCommand::Clear();

            Renderer::BeginScene();

            m_ShaderProgram->Bind();
            Renderer::Submit(m_VertexArray);

            Renderer::EndScene();

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