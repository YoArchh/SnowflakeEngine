#pragma once

#include "Layers/Layer.h"

namespace Snowflake
{
    class ImGuiLayer : public Layer
    {
    public:
        virtual void Begin() = 0;
        virtual void End() = 0;

        void SetDarkThemeColors();

        static ImGuiLayer* Create();
    };
}
