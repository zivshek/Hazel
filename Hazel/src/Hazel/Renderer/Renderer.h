#pragma once
#include "Hazel/Core.h"
#include "RenderCommand.h"
#include "Camera.h"
#include "Shader.h"

namespace Hazel
{
    class Renderer
    {
    public:
        static void Init();
        static void BeginScene(OrthographicCamera& camera);
        static void EndScene();
        static void Submit(const Ref<Shader>& shader, const Ref<VertexArray>& vertexArray, const glm::mat4& transform = glm::mat4(1.0f));

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