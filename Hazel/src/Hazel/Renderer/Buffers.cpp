#include "pch.h"
#include "Buffers.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffers.h"

namespace Hazel
{
    BufferLayout::BufferLayout(const std::initializer_list<BufferElement>& elements)
        : m_Elements{ elements }, m_Stride{ 0 }
    {
        uint offset = 0;
        for (auto& element : m_Elements)
        {
            element.Offset = offset;
            offset += element.Size;
            m_Stride += element.Size;
        }
    }

    Hazel::VertexBuffer* VertexBuffer::Create(float* vertices, uint size)
    {
        switch (Renderer::GetAPI())
        {
        case Renderer::API::OpenGL:
            return new OpenGLVertextBuffer(vertices, size);
        default:
            HZ_CORE_ASSERT(false, "RendererAPI::{0} is not supported yet", static_cast<int>(Renderer::GetAPI()));
            return nullptr;
        }
    }

    Hazel::IndexBuffer* IndexBuffer::Create(uint* indices, uint count)
    {
        switch (Renderer::GetAPI())
        {
        case Renderer::API::OpenGL:
            return new OpenGLIndexBuffer(indices, count);
        default:
            HZ_CORE_ASSERT(false, "RendererAPI::{0} is not supported yet", static_cast<int>(Renderer::GetAPI()));
            return nullptr;
        }
    }
}