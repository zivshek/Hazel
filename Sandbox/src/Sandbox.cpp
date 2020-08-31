#pragma once

#include <Hazel.h>

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example Layer")
        , m_VertexArray{ Hazel::VertexArray::Create() }
        , m_OrthoCamera{ -1.0f, 1.0f, -1.0f, 1.0f }
        , m_CameraPosition{ 0 }
        , m_CameraSpeed{ 1.0f }
    {
        float vertices[3 * 7] = {
                0.0f, 0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f,
                -0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 1.0f, 1.0f
        };
        uint indices[3] = { 0, 2, 1 };

        auto vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof vertices);
        vertexBuffer->SetLayout(
            {
                { Hazel::ShaderDataType::Float3, "a_Position" },
                { Hazel::ShaderDataType::Float4, "a_Color"}
            });
        auto indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(float));

        m_VertexArray->AddVertexBuffer(vertexBuffer);
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec4 a_Color;

            uniform mat4 u_ViewProjMat;

            out vec4 v_Color;

            void main()
            {
                v_Color = a_Color;
                gl_Position = u_ViewProjMat * vec4(a_Position, 1.0);
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
        m_Shader = std::make_shared<Hazel::ShaderProgram>(vertexSrc, fragSrc);
    }
    ~ExampleLayer() {}

    void OnUpdate(Hazel::Timestep deltaTime) override
    {
        if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_W))
            m_CameraPosition.y += m_CameraSpeed * deltaTime.GetSeconds();
        else if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_S))
            m_CameraPosition.y -= m_CameraSpeed * deltaTime.GetSeconds();

        if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_A))
            m_CameraPosition.x -= m_CameraSpeed * deltaTime.GetSeconds();
        else if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_D))
            m_CameraPosition.x += m_CameraSpeed * deltaTime.GetSeconds();

        m_OrthoCamera.SetPosition(m_CameraPosition);
    }

    void OnDraw() override
    {
        Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Hazel::RenderCommand::Clear();

        Hazel::Renderer::BeginScene(m_OrthoCamera);
        Hazel::Renderer::Submit(m_Shader, m_VertexArray);
        Hazel::Renderer::EndScene();
    }
    void OnAttach() override {}
    void OnDetach() override {}
    void OnEvent(Hazel::Event& e) override {}
    void OnDrawImGui() override {}
private:
    std::shared_ptr<Hazel::ShaderProgram> m_Shader;
    std::shared_ptr<Hazel::VertexArray> m_VertexArray;
    Hazel::OrthographicCamera m_OrthoCamera;
    glm::vec3 m_CameraPosition;
    float m_CameraSpeed;
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        PushLayer(new ExampleLayer());
    };
    ~Sandbox() {};
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox();
}