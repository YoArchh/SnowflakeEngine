#pragma once

#include "Events/Event.h"

namespace Snowflake
{
    class Layer
    {
    public:
        Layer(const std::string& Name = "Layer");
        virtual ~Layer() = default;

        virtual void OnAttach() {}
        virtual void OnDetach() {}
        virtual void OnUpdate() {}
        virtual void OnTick() {}
        virtual void OnUIRender() {}
        virtual void OnEvent(Event& InEvent) {}

        inline const std::string& GetName() const { return m_Name; }

    protected:
        std::string m_Name;
    };
}
