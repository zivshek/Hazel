#include "pch.h"
#include "Layer.h"

namespace Hazel
{
    Layer::Layer(const std::string& name /* = "Layer" */)
        : m_DebugName{ name }
    {
    }

    Layer::~Layer()
    {
    }
}