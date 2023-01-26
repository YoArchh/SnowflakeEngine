#pragma once

#include "Input/Input.h"

namespace Snowflake
{
    class WindowsInput : public Input
    {
    public:
        virtual bool GetKeyDown_Implementation(Key InKey) override;
        virtual bool GetKeyUp_Implementation(Key InKey) override;

        virtual bool GetMouseButtonDown_Implementation(MouseButton InMouseButton) override;
        virtual bool GetMouseButtonUp_Implementation(MouseButton InMouseButton) override;

        virtual glm::vec2 GetMousePosition_Implementation() override;

        virtual bool GetGamepadButtonDown_Implementation(GamepadID InGamepadID, GamepadButton InGamepadButton) override;

        virtual float GetGamepadAxis_Implementation(GamepadID InGamepadID, GamepadAxis InGamepadAxis) override;
    };

}