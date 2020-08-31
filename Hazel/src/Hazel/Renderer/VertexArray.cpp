#include "pch.h"
#include "VertexArray.h"
#include "Platform/OpenGL/OpenGLVertexArray.h"
#include "Renderer.h"

namespace Hazel
{
    Ref<VertexArray> VertexArray::Create()
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return Ref<OpenGLVertexArray>(new OpenGLVertexArray());
            break;
        }

        return nullptr;
    }
}