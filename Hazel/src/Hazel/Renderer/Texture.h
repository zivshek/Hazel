#pragma once

#include "Hazel/Core/Core.h"

namespace Hazel
{
    class Texture
    {
    public:
        virtual ~Texture() {}

        virtual uint GetWidth() const { return m_Width; }
        virtual uint GetHeight() const { return m_Height; }

        virtual void Bind(uint slot = 0) const = 0;

    protected:
        uint m_Width, m_Height;
    };

    class Texture2D : public Texture
    {
    public:
        static Ref<Texture2D> Create(const char* path);
    };
}