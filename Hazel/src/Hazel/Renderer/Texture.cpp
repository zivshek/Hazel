#include "pch.h"
#include "Texture.h"

#include "Renderer.h"
#include "Platform/OpenGL/OpenGLTexture.h"

namespace Hazel
{
    Ref<Texture2D> Texture2D::Create(const char* path)
    {
        switch (Renderer::GetAPI())
        {
        case RenderAPI::API::OpenGL:
            return Ref<OpenGLTexture2D>(new OpenGLTexture2D(path));
        }

        return nullptr;
    }
}