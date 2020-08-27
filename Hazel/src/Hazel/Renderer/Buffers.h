#pragma once
#include "Hazel/Core.h"

namespace Hazel
{
    class VertexBuffer
    {
    public:
        virtual ~VertexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;

        static VertexBuffer* Create(float* vertices, uint size);
    };

    class IndexBuffer
    {
    public:
        virtual ~IndexBuffer() {}

        virtual void Bind() const = 0;
        virtual void Unbind() const = 0;
        virtual uint GetCount() const = 0;

        static IndexBuffer* Create(uint* indices, uint count);
    };
}