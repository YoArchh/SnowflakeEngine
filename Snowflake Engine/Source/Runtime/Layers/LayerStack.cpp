#include "SnowflakePCH.h"
#include "LayerStack.h"

namespace Snowflake
{
    void LayerStack::PushLayer(Layer* InLayer)
    {
        m_Layers.emplace(m_Layers.begin() + m_LayerInsertIndex, InLayer);
        m_LayerInsertIndex++;

        InLayer->OnAttach();
    }

    void LayerStack::PopLayer(Layer* InLayer)
    {
        auto Iterator = std::find(m_Layers.begin(), m_Layers.end(), InLayer);
        if (Iterator != m_Layers.end())
        {
            m_Layers.erase(Iterator);
            m_LayerInsertIndex--;
        }

        InLayer->OnDetach();
    }

    void LayerStack::PushOverlay(Layer* Overlay)
    {
        m_Layers.emplace_back(Overlay);

        Overlay->OnAttach();
    }

    void LayerStack::PopOverlay(Layer* Overlay)
    {
        auto Iterator = std::find(m_Layers.begin(), m_Layers.end(), Overlay);
        if (Iterator != m_Layers.end())
            m_Layers.erase(Iterator);

        Overlay->OnDetach();
    }
}
