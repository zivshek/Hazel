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

        static Ref<Shader> Create(const std::string& file);
    };
}