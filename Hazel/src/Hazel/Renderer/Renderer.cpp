#include "pch.h"
#include "Renderer.h"

namespace Hazel
{
    std::unique_ptr<Renderer::SceneData> Renderer::s_SceneData = std::make_unique<Renderer::SceneData>();

    void Renderer::BeginScene(OrthographicCamera& camera)
    {
        s_SceneData->ViewProjMat = camera.GetViewProjMatrix();
    }

    void Renderer::EndScene()
    {
    }

    void Renderer::Submit(const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<VertexArray>& vertexArray)
    {
        shader->Bind();
        shader->SetUniform("u_ViewProjMat", s_SceneData->ViewProjMat);

        vertexArray->Bind();
        RenderCommand::DrawIndexed(vertexArray);
    }
}