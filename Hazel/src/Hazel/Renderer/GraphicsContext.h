#pragma once

#include "Hazel/Core.h"

namespace Hazel
{
    class GraphicsContext
    {
    public:
        virtual ~GraphicsContext() {}
        virtual void Init() = 0;
        virtual void SwapBuffers() = 0;
    };
}