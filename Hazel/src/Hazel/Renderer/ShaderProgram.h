#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
    class ShaderProgram
    {
    public:
        ShaderProgram(const std::string& vertexSource, const std::string& fragmentSource);
        ~ShaderProgram();

        void Bind();
        void Unbind();

    private:
        uint m_Program;
    };
}