#include "Sandbox2D.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Platform/OpenGL/OpenGLShader.h"

#include "imgui.h"

Sandbox2D::Sandbox2D()
    : Layer("Sandbox2D")
    , m_VertexArray{ Hazel::VertexArray::Create() }
    , m_CameraController{ 16.0f / 9.0f }
    , m_FlatColor{ 1.0f, 0, 0, 1.0f }
{
}

Sandbox2D::~Sandbox2D()
{
}

void Sandbox2D::OnAttach()
{
    float vertices[4 * 3] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
        -0.5f,  0.5f, 0.0f,
         0.5f,  0.5f, 0.0f
    };

    uint indices[6] = { 0, 1, 2, 2, 1, 3 };

    auto vertexBuffer = Hazel::VertexBuffer::Create(vertices, sizeof vertices);
    vertexBuffer->SetLayout(
        {
            { Hazel::ShaderDataType::Float3, "a_Position" },
        });
    m_VertexArray->AddVertexBuffer(vertexBuffer);

    auto indexBuffer = Hazel::IndexBuffer::Create(indices, sizeof(indices) / sizeof(float));
    m_VertexArray->SetIndexBuffer(indexBuffer);

    Hazel::Renderer::GetShaderLibrary().Load("assets/shaders/FlatColorShader.glsl");
}

void Sandbox2D::OnDetach()
{
}

void Sandbox2D::OnUpdate(Hazel::Timestep deltaTime)
{
    m_CameraController.OnUpdate(deltaTime);
}

void Sandbox2D::OnDraw()
{
    Hazel::RenderCommand::SetClearColor({ 0.1f, 0.1f, 0.1f, 1 });
    Hazel::RenderCommand::Clear();

    Hazel::Renderer::BeginScene(m_CameraController.GetCamera());
    std::dynamic_pointer_cast<Hazel::OpenGLShader>(Hazel::Renderer::GetShaderLibrary().Get("FlatColorShader"))->Bind();
    std::dynamic_pointer_cast<Hazel::OpenGLShader>(Hazel::Renderer::GetShaderLibrary().Get("FlatColorShader"))->SetUniformVec4("u_Color", m_FlatColor);
    Hazel::Renderer::Submit(Hazel::Renderer::GetShaderLibrary().Get("FlatColorShader"), m_VertexArray);
    Hazel::Renderer::EndScene();
}

void Sandbox2D::OnEvent(Hazel::Event& e)
{
    m_CameraController.OnEvent(e);
}

void Sandbox2D::OnDrawImGui()
{
    ImGui::Begin("Color");
    ImGui::ColorEdit4("Color", glm::value_ptr(m_FlatColor));
    ImGui::End();
}