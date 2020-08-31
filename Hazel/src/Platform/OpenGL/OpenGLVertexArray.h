#pragma once
#include "Hazel/Renderer/VertexArray.h"
#include "Hazel/Renderer/Buffers.h"

namespace Hazel
{
    class OpenGLVertexArray : public VertexArray
    {
    public:
        OpenGLVertexArray();
        ~OpenGLVertexArray();
        void Bind() override;
        void Unbind() override;
        void AddVertexBuffer(const Ref<VertexBuffer>& vertextBuffer) override;
        void SetIndexBuffer(const Ref<IndexBuffer>& indexBuffer) override;
        const std::vector<Ref<VertexBuffer>>& GetVertexBuffers() const override { return m_VertexBuffers; }
        const Ref<IndexBuffer>& GetIndexBuffer() const override { return m_IndexBuffer; }

    private:
        uint m_Id;
        std::vector<Ref<VertexBuffer>> m_VertexBuffers;
        Ref<IndexBuffer> m_IndexBuffer;
    };
}