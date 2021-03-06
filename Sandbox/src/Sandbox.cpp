#pragma once
#include <Hazel.h>
#include <Hazel/Core/EntryPoint.h>
#include <glm/gtc/matrix_transform.hpp>

#include "Platform/OpenGL/OpenGLShader.h"
#include "Sandbox2D.h"

class ExampleLayer : public Hazel::Layer
{
public:
    ExampleLayer()
        : Layer("Example Layer")
        , m_VertexArray{ Hazel::VertexArray::Create() }
        , m_CameraController{ 16.0f / 9.0f }
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

        Hazel::Renderer::GetShaderLibrary().Load("assets/shaders/TextureShader.glsl");

        m_CheckerBoardTexture = Hazel::Texture2D::Create("assets/Checkerboard.png");
        m_RegularTexture = Hazel::Texture2D::Create("assets/Ins.png");
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(Hazel::Renderer::GetShaderLibrary().Get("TextureShader"))->Bind();
        std::dynamic_pointer_cast<Hazel::OpenGLShader>(Hazel::Renderer::GetShaderLibrary().Get("TextureShader"))->SetUniformInt("u_Texture", 0);
    }
    ~ExampleLayer() {}

    void OnUpdate(Hazel::Timestep deltaTime) override
    {
        m_CameraController.OnUpdate(deltaTime);
    }

    void OnDraw() override
    {
        Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
        Hazel::RenderCommand::Clear();

        Hazel::Renderer::BeginScene(m_CameraController.GetCamera());
        m_CheckerBoardTexture->Bind();
        Hazel::Renderer::Submit(Hazel::Renderer::GetShaderLibrary().Get("TextureShader"), m_VertexArray);
        m_RegularTexture->Bind();
        Hazel::Renderer::Submit(Hazel::Renderer::GetShaderLibrary().Get("TextureShader"), m_VertexArray);
        Hazel::Renderer::EndScene();
    }
    void OnAttach() override {}
    void OnDetach() override {}
    void OnEvent(Hazel::Event& e) override
    {
        m_CameraController.OnEvent(e);
    }
    void OnDrawImGui() override {}
private:
    Hazel::Ref<Hazel::VertexArray> m_VertexArray;
    Hazel::Ref<Hazel::Texture2D> m_CheckerBoardTexture;
    Hazel::Ref<Hazel::Texture2D> m_RegularTexture;
    Hazel::OrthoCameraController m_CameraController;
};

class Sandbox : public Hazel::Application
{
public:
    Sandbox()
    {
        //PushLayer(new ExampleLayer());
        PushLayer(new Sandbox2D());
    };
    ~Sandbox() {};
};

Hazel::Application* Hazel::CreateApplication()
{
    return new Sandbox();
}