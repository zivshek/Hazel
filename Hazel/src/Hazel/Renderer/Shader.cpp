#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"

namespace Hazel
{
    Ref<Shader> Shader::Create(const std::string& file)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return Ref<OpenGLShader>(new OpenGLShader(file));
        }
        HZ_CORE_ASSERT(false, "Unsupported API");
        return nullptr;
    }
}