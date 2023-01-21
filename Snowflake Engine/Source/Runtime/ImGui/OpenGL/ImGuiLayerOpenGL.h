#pragma once

#include "ImGui/ImGuiLayer.h"

namespace Snowflake
{
    class ImGuiLayerOpenGL : public ImGuiLayer
    {
    public:
        ImGuiLayerOpenGL() = default;
        virtual ~ImGuiLayerOpenGL() = default;

        virtual void Begin() override;
        virtual void End() override;

        virtual void OnAttach() override;
        virtual void OnDetach() override;
        virtual void OnUIRender() override;
    };
}
