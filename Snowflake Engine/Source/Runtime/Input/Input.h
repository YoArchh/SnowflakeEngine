#pragma once

#include "Keys.h"

#include "Core/Math/Vector2.h"

namespace Snowflake
{
    class Input
    {
    public:
        static bool GetKeyDown(Key InKey) { return s_Instance->GetKeyDown_Implementation(InKey); }
        static bool GetKeyUp(Key InKey) { return s_Instance->GetKeyUp_Implementation(InKey); }

        static bool GetMouseButtonDown(MouseButton InMouseButton) { return s_Instance->GetMouseButtonDown_Implementation(InMouseButton); }
        static bool GetMouseButtonUp(MouseButton InMouseButton) { return s_Instance->GetMouseButtonUp_Implementation(InMouseButton); }

        static Vector2 GetMousePosition() { return s_Instance->GetMousePosition_Implementation(); }

        static bool GetGamepadButtonDown(GamepadID InGamepadID, GamepadButton InGamepadButton)
        {
            return s_Instance->GetGamepadButtonDown_Implementation(InGamepadID, InGamepadButton);
        }

        static float GetGamepadAxis(GamepadID InGamepadID, GamepadAxis InGamepadAxis)
        {
            return s_Instance->GetGamepadAxis_Implementation(InGamepadID, InGamepadAxis);
        }
    protected:
        virtual bool GetKeyDown_Implementation(Key InKey) = 0;
        virtual bool GetKeyUp_Implementation(Key InKey) = 0;

        virtual bool GetMouseButtonDown_Implementation(MouseButton InMouseButton) = 0;
        virtual bool GetMouseButtonUp_Implementation(MouseButton InMouseButton) = 0;

        virtual Vector2 GetMousePosition_Implementation() = 0;

        virtual bool GetGamepadButtonDown_Implementation(GamepadID InGamepadID, GamepadButton InGamepadButton) = 0;

        virtual float GetGamepadAxis_Implementation(GamepadID InGamepadID, GamepadAxis InGamepadAxis) = 0;
        
    private:
        static void Initialize();

    private:
        static Input* s_Instance;
        
        friend class Application;
    };
}
