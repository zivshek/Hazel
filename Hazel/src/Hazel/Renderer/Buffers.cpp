#include "pch.h"
#include "Buffers.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLBuffers.h"

namespace Hazel
{
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