#include "pch.h"
#include "OpenGLRenderAPI.h"

#include <glad/glad.h>

namespace Hazel
{
    void OpenGLRenderAPI::Init()
    {
        auto version = glGetString(GL_VERSION);
        std::stringstream ss((const char*)version);
        uint major, minor;
        ss >> major; ss.ignore(); ss >> minor;
        RenderAPI::SetVersion({ major, minor });

        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    void OpenGLRenderAPI::SetViewport(uint w, uint h)
    {
        glViewport(0, 0, w, h);
    }

    void OpenGLRenderAPI::Clear()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    }

    void OpenGLRenderAPI::SetClearColor(const glm::vec4& color)
    {
        glClearColor(color.r, color.g, color.b, color.a);
    }

    void OpenGLRenderAPI::DrawIndexed(const Ref<VertexArray>& vertexArray)
    {
        glDrawElements(GL_TRIANGLES, vertexArray->GetIndexBuffer()->GetCount(), GL_UNSIGNED_INT, nullptr);
    }
}