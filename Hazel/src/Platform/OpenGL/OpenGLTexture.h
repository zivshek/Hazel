#pragma once
#include "Hazel/Core/Core.h"
#include "Hazel/Renderer/Texture.h"

namespace Hazel
{
    class OpenGLTexture2D : public Texture2D
    {
    public:
        OpenGLTexture2D(const char* path);
        ~OpenGLTexture2D();
        void Bind(uint slot = 0) const override;

    private:
        uint m_Id;
    };
}