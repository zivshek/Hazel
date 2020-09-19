#pragma once

#include "Hazel/Core/Core.h"
#include "Hazel/Renderer/Buffers.h"

namespace Hazel
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(float* vertices, uint size);
        ~OpenGLVertexBuffer();

        void Bind() const override;
        void Unbind() const override;

        inline void SetLayout(const BufferLayout& layout) override { m_Layout = layout; }
        inline const BufferLayout& GetLayout() const override { return m_Layout; }
    private:
        uint m_Id;
        BufferLayout m_Layout;
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