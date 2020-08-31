#pragma once
#include "Hazel/Core.h"

#include "glm/glm.hpp"
#include "VertexArray.h"

namespace Hazel
{
    class RenderAPI
    {
    public:
        enum class API
        {
            OpenGL, None
        };

        virtual void Clear() = 0;
        virtual void SetClearColor(const glm::vec4& color) = 0;
        virtual void DrawIndexed(const Ref<VertexArray>& vertexArray) = 0;

        inline static API GetAPI() { return s_API; }
    private:
        static API s_API;
    };
}