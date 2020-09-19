#pragma once
#include "Hazel/Core/Core.h"
#include "Hazel/Renderer/RenderAPI.h"

namespace Hazel
{
    class OpenGLRenderAPI : public RenderAPI
    {
    public:
        void Init() override;

        void SetViewport(uint w, uint h) override;

        void Clear() override;

        void SetClearColor(const glm::vec4& color) override;

        void DrawIndexed(const Ref<VertexArray>& vertexArray) override;
    };
}