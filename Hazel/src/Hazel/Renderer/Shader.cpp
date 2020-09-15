#include "pch.h"
#include "Shader.h"
#include "Renderer.h"
#include "Platform/OpenGL/OpenGLShader.h"
#include "Hazel/Utils/Utils.h"

namespace Hazel
{
    Ref<Shader> Shader::Create(const std::string& name, const std::string& file)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return Ref<OpenGLShader>(new OpenGLShader(name, file));
        }
        HZ_CORE_ASSERT(false, "Unsupported API");
        return nullptr;
    }

    void ShaderLibrary::Add(Ref<Shader> shader)
    {
        HZ_CORE_ASSERT(m_shaderMap.find(shader->GetName()) == m_shaderMap.end(), "Shader already exists");
        m_shaderMap[shader->GetName()] = shader;
    }

    Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string& name, const std::string& file)
    {
        Utils::LoadFile(file.c_str());
        m_shaderMap[name] = Shader::Create(name, file);
        return m_shaderMap[name];
    }

    Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const std::string& file)
    {
        return Load(file.c_str());
    }

    Hazel::Ref<Hazel::Shader> ShaderLibrary::Load(const char* file)
    {
        auto name = Utils::GetFileNameWithoutExt(file);
        return Load(name, file);
    }

    Hazel::Ref<Hazel::Shader> ShaderLibrary::Get(const std::string& name)
    {
        HZ_CORE_ASSERT(m_shaderMap.find(name) != m_shaderMap.end(), "Shader doesn't exist");
        return m_shaderMap[name];
    }
}