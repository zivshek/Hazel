#pragma once

#include "Hazel/Core.h"
#include "Hazel/Renderer/Buffers.h"

namespace Hazel
{
    class OpenGLVertextBuffer : public VertexBuffer
    {
    public:
        OpenGLVertextBuffer(float* vertices, uint size);
        ~OpenGLVertextBuffer();

        void Bind() const override;
        void Unbind() const override;
    private:
        uint m_Id;
    };

    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(uint* indices, uint count);
        ~OpenGLIndexBuffer();

        void Bind() const override;
        void Unbind() const override;
        inline uint GetCount() const override { return m_Count; };

    private:
        uint m_Id;
        uint m_Count;
    };
}