#include "pch.h"
#include "LayerStack.h"

namespace Hazel
{
    LayerStack::LayerStack()
        : m_LayerInsertIndex{ 0 }
        , m_Layers{}
    {
    }

    LayerStack::~LayerStack()
    {
        for (auto layer : m_Layers)
        {
            layer->OnDetach();
            delete layer;
        }
    }

    void LayerStack::Push(Layer* layer)
    {
        m_Layers.emplace(begin() + m_LayerInsertIndex, layer);
        m_LayerInsertIndex++;
    }

    void LayerStack::PushOverlay(Layer* layer)
    {
        m_Layers.emplace_back(layer);
    }

    void LayerStack::Pop(Layer* layer)
    {
        auto it = std::find(m_Layers.begin(), m_Layers.begin() + m_LayerInsertIndex, layer);
        if (it != m_Layers.begin() + m_LayerInsertIndex)
        {
            layer->OnDetach();
            m_Layers.erase(it);
            m_LayerInsertIndex--;
        }
    }

    void LayerStack::PopOverlay(Layer* layer)
    {
        auto it = std::find(m_Layers.begin() + m_LayerInsertIndex, m_Layers.end(), layer);
        if (it != m_Layers.end())
        {
            layer->OnDetach();
            m_Layers.erase(it);
        }
    }
}