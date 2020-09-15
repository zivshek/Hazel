#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
    class Shader
    {
    public:
        virtual ~Shader() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        const std::string& GetName() const { return m_Name; }

        static Ref<Shader> Create(const std::string& name, const std::string& file);
    protected:
        std::string m_Name;
    };

    class ShaderLibrary
    {
    public:
        void Add(Ref<Shader> shader);
        Ref<Shader> Load(const std::string& name, const std::string& file);
        Ref<Shader> Load(const std::string& file);
        Ref<Shader> Load(const char* file);
        Ref<Shader> Get(const std::string& name);
    private:
        std::unordered_map<std::string, Ref<Shader>> m_shaderMap;
    };
}