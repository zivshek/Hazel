#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
    class ShaderProgram
    {
    public:
        virtual ~ShaderProgram() {}

        virtual void Bind() = 0;
        virtual void Unbind() = 0;

        static Ref<ShaderProgram> Create(const std::string& vertexSource, const std::string& fragmentSource);
    };
}