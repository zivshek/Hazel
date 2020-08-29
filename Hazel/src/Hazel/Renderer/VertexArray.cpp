#include "pch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Hazel
{
    std::shared_ptr<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case Renderer::API::OpenGL:
            return std::make_shared<OpenGLVertexArray>();
            break;
        }

        return nullptr;
    }
}