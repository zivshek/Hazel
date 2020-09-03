#pragma once
#include "Hazel/Core.h"
#include "RenderAPI.h"

namespace Hazel
{
    class RenderCommand
    {
    public:
        static void Init()
        {
            s_RenderAPI->Init();
        }

        static void SetClearColor(const glm::vec4& color)
        {
            s_RenderAPI->SetClearColor(color);
        }

        static void Clear()
        {
            s_RenderAPI->Clear();
        }

        static void DrawIndexed(const Ref<VertexArray>& vertexArray)
        {
            s_RenderAPI->DrawIndexed(vertexArray);
        }
    private:
        static RenderAPI* s_RenderAPI;
    };
}