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

    static GLenum ShaderDataTypeToOpenGLBaseType(ShaderDataType type)
    {
        switch (type)
        {
        case Hazel::ShaderDataType::Float:    return GL_FLOAT;
        case Hazel::ShaderDataType::Float2:   return GL_FLOAT;
        case Hazel::ShaderDataType::Float3:   return GL_FLOAT;
        case Hazel::ShaderDataType::Float4:   return GL_FLOAT;
        case Hazel::ShaderDataType::Mat3:     return GL_FLOAT;
        case Hazel::ShaderDataType::Mat4:     return GL_FLOAT;
        case Hazel::ShaderDataType::Int:      return GL_INT;
        case Hazel::ShaderDataType::Int2:     return GL_INT;
        case Hazel::ShaderDataType::Int3:     return GL_INT;
        case Hazel::ShaderDataType::Int4:     return GL_INT;
        case Hazel::ShaderDataType::Bool:     return GL_BOOL;
        }

        HZ_CORE_ASSERT(false, "Unknown ShaderDataType!");
        return 0;
    }

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

        float vertices[3 * 7] = {
            0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
            -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };
        m_VertexBuffer.reset(VertexBuffer::Create(vertices, sizeof vertices));

        BufferLayout layout = {
            { ShaderDataType::Float3, "a_Position" },
            { ShaderDataType::Float4, "a_Color"}
        };

        uint i = 0;
        for (const auto& element : layout)
        {
            glEnableVertexAttribArray(i);
            glVertexAttribPointer(i,
                ShaderDataTypeCount(element.Type),
                ShaderDataTypeToOpenGLBaseType(element.Type),
                element.Normalized,
                layout.GetStride(),
                (const void*)element.Offset);
            i++;
        }

        uint indices[3] = { 0, 2, 1 };
        m_IndexBuffer.reset(IndexBuffer::Create(indices, 3));

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
            glDrawElements(GL_TRIANGLES, m_IndexBuffer->GetCount(), GL_UNSIGNED_INT, nullptr);

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