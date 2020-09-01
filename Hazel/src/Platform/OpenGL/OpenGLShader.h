#pragma once

#include "Hazel/Core.h"
#include "Hazel/Renderer/ShaderProgram.h"

#include <glm/glm.hpp>

namespace Hazel
{
    class OpenGLShader : public ShaderProgram
    {
    public:
        OpenGLShader(const std::string& vertexSource, const std::string& fragmentSource);
        ~OpenGLShader();

        void Bind();
        void Unbind();

        void SetUniformMat4(const std::string& uniform, const glm::mat4& mat);
        void SetUniformVec3(const std::string& uniform, const glm::vec3& vec);
        void SetUniformInt(const std::string& uniform, const int i);
    private:
        uint m_Program;
    };
}