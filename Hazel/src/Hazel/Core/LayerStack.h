#pragma once

#include "Layer.h"

namespace Hazel
{
    class  LayerStack
    {
    public:
        LayerStack();
        ~LayerStack();

        void Push(Layer* layer);
        void PushOverlay(Layer* layer);
        void Pop(Layer* layer);
        void PopOverlay(Layer* layer);

        typedef std::vector<Layer*> Layers;

        inline Layers::iterator begin() { return m_Layers.begin(); }
        inline Layers::iterator end() { return m_Layers.end(); }

    private:
        Layers m_Layers;
        uint m_LayerInsertIndex;
    };
}
