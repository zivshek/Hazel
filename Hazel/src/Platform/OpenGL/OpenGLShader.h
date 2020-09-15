#pragma once

#include "Hazel/Core.h"
#include "Hazel/Renderer/Shader.h"

#include <glm/glm.hpp>

namespace Hazel
{
    class OpenGLShader : public Shader
    {
    public:
        OpenGLShader(const std::string& name, const std::string& file);
        ~OpenGLShader();

        void Bind() override;
        void Unbind() override;

        void SetUniformMat4(const std::string& uniform, const glm::mat4& mat);
        void SetUniformVec3(const std::string& uniform, const glm::vec3& vec);
        void SetUniformInt(const std::string& uniform, const int i);
    private:
        void Process(const std::string& file);

        uint m_Program;
    };
}