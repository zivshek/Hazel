#include "pch.h"
#include "ShaderProgram.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
    Ref<ShaderProgram> ShaderProgram::Create(const std::string& vertexSource, const std::string& fragmentSource)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return Ref<OpenGLShader>(new OpenGLShader(vertexSource, fragmentSource));
        }
        HZ_CORE_ASSERT(false, "Unsupported API");
        return nullptr;
    }
}