#pragma once
#include "Hazel/Core.h"
#include "Buffers.h"

namespace Hazel
{
    class VertexArray
    {
    public:
        virtual ~VertexArray() {}
        virtual void Bind() = 0;
        virtual void Unbind() = 0;
        virtual void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertextBuffer) = 0;
        virtual void SetIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer) = 0;
        virtual const std::vector<std::shared_ptr<VertexBuffer>>& GetVertexBuffers() const = 0;
        virtual const std::shared_ptr<IndexBuffer>& GetIndexBuffer() const = 0;

        static std::shared_ptr<VertexArray> Create();
    };
}