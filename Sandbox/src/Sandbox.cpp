#pragma once

#include <Hazel.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example Layer")
        , m_VertexArray{ Hazel::VertexArray::Create() }
        , m_OrthoCamera{ -1.6f, 1.6f, -0.9f, 0.9f }
        , m_CameraPosition{ 0 }
        , m_CameraSpeed{ 1.0f }
    {
        float vertices[4 * 5] = {
                -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
                0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
                -0.5f, 0.5f, 0.0f, 0.0f, 1.0f,
                0.5f, 0.5f, 0.0f, 1.0f, 1.0f
        };
        uint indices[6] = { 0, 1, 2, 2, 1, 3 };

        auto vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof vertices);
        vertexBuffer->SetLayout(
            {
                { Hazel::ShaderDataType::Float3, "a_Position" },
                { Hazel::ShaderDataType::Float2, "a_UV"}
            });
        m_VertexArray->AddVertexBuffer(vertexBuffer);

        auto indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(float));
        m_VertexArray->SetIndexBuffer(indexBuffer);

        std::string vertexSrc = R"(
            #version 330 core
            layout(location = 0) in vec3 a_Position;
            layout(location = 1) in vec2 a_UV;

            uniform mat4 u_ViewProjMat;
            uniform mat4 u_Transform;

            out vec2 v_UV;

            void main()
            {
                v_UV = a_UV;
                gl_Position = u_ViewProjMat * u_Transform * vec4(a_Position, 1.0);
            }
        )";

        std::string fragSrc = R"(
            #version 330 core
            layout(location = 0) out vec4 color;
            in vec2 v_UV;

            uniform sampler2D u_Texture;

            void main()
            {
                color = texture(u_Texture, v_UV);
            }
        )";
        m_Shader = Hazel::ShaderProgram::Create(vertexSrc, fragSrc);

        m_CheckerBoardTexture = Hazel::Texture2D::Create("assets/Checkerboard.png");
        m_RegularTexture = Hazel::Texture2D::Create("assets/conan.png");
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->Bind();
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(m_Shader)->SetUniformInt("u_Texture", 0);
    }
    ~ExampleLayer() {}

    void OnUpdate(Hazel::Timestep deltaTime) override
    {
        if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_W))
            m_CameraPosition.y += m_CameraSpeed * deltaTime;
        else if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_S))
            m_CameraPosition.y -= m_CameraSpeed * deltaTime;

        if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_A))
            m_CameraPosition.x -= m_CameraSpeed * deltaTime;
        else if (Hazel::Input::Get().IsKeyPressed(HZ_KEY_D))
            m_CameraPosition.x += m_CameraSpeed * deltaTime;

        m_OrthoCamera.SetPosition(m_CameraPosition);
    }

    void OnDraw() override
    {
        Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Hazel::RenderCommand::Clear();

        Hazel::Renderer::BeginScene(m_OrthoCamera);
        m_CheckerBoardTexture->Bind();
        Hazel::Renderer::Submit(m_Shader, m_VertexArray);
        m_RegularTexture->Bind();
        Hazel::Renderer::Submit(m_Shader, m_VertexArray, glm::translate(glm::mat4(1.0f), glm::vec3(0.55f, 0, 0)));
        Hazel::Renderer::EndScene();
    }
    void OnAttach() override {}
    void OnDetach() override {}
    void OnEvent(Hazel::Event& e) override {}
    void OnDrawImGui() override {}
private:
    Hazel::Ref<Hazel::ShaderProgram> m_Shader;
    Hazel::Ref<Hazel::VertexArray> m_VertexArray;
    Hazel::Ref<Hazel::Texture2D> m_CheckerBoardTexture;
    Hazel::Ref<Hazel::Texture2D> m_RegularTexture;
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