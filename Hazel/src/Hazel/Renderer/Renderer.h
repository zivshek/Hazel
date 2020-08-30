#pragma once
#include "Hazel/Core.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "ShaderProgram.h"

namespace Hazel
{
    class Renderer
    {
    public:
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        static void Submit(const std::shared_ptr<ShaderProgram>& shader, const std::shared_ptr<VertexArray>& vertexArray);

        inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }

    public:
        struct SceneData
        {
            glm::mat4 ViewProjMat;
        };

    private:
        static std::unique_ptr<SceneData> s_SceneData;
    };
}