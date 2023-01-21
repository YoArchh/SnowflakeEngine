#pragma once

#include "Core/Assertion.h"

#include "Layer.h"

namespace Snowflake
{
    class LayerStack
    {
    public:
        LayerStack() = default;
        ~LayerStack() = default;

        void PushLayer(Layer* InLayer);
        void PopLayer(Layer* InLayer);

        void PushOverlay(Layer* Overlay);
        void PopOverlay(Layer* Overlay);

        size_t Size() const { return m_Layers.size(); }

        std::vector<Layer*>::iterator begin() { return m_Layers.begin(); }
        std::vector<Layer*>::iterator end() { return m_Layers.end(); }
        
        Layer* operator[](size_t Index)
        {
            ENGINE_ASSERT(Index >= 0 && Index < m_Layers.size())
            return m_Layers[Index];
        }
        
    private:
        std::vector<Layer*> m_Layers;
        unsigned int m_LayerInsertIndex = 0;
    };
}
