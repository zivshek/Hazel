#pragma once
#include "Hazel/Core.h"
#include "RenderCommand.h"

namespace Hazel
{
    class Renderer
    {
    public:
        static void BeginScene();
        static void EndScene();
        static void Submit(const std::shared_ptr<VertexArray>& vertexArray);

        inline static RenderAPI::API GetAPI() { return RenderAPI::GetAPI(); }
    };
}