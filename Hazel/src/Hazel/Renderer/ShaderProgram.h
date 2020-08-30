#pragma once

#include "Hazel/Core.h"

#include <glm/glm.hpp>

namespace Hazel
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
        ~ShaderProgram();

        void Bind();
        void Unbind();

        void SetUniform(const std::string uniform, const glm::mat4& mat);
    private:
        uint m_Program;
    };
}