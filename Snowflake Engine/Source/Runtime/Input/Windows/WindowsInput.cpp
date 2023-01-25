#include "SnowflakePCH.h"
#include "WindowsInput.h"

#include "Application/Application.h"

#include <GLFW/glfw3.h>

namespace Snowflake
{
    bool WindowsInput::GetKeyDown_Implementation(Key InKey)
    {
        auto* Window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetHandle());

        return glfwGetKey(Window, InKey.GetValue()) == GLFW_PRESS;
    }

    bool WindowsInput::GetKeyUp_Implementation(Key InKey)
    {
        auto* Window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetHandle());

        return glfwGetKey(Window, InKey.GetValue()) == GLFW_RELEASE;
    }

    bool WindowsInput::GetMouseButtonDown_Implementation(MouseButton InMouseButton)
    {
        auto* Window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetHandle());

        return glfwGetMouseButton(Window, InMouseButton.GetValue()) == GLFW_PRESS;
    }

    bool WindowsInput::GetMouseButtonUp_Implementation(MouseButton InMouseButton)
    {
        auto* Window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetHandle());

        return glfwGetMouseButton(Window, InMouseButton.GetValue()) == GLFW_RELEASE;
    }

    Vector2 WindowsInput::GetMousePosition_Implementation()
    {
        auto* Window = static_cast<GLFWwindow*>(Application::GetInstance().GetWindow().GetHandle());
        double XPos, YPos;
        
        glfwGetCursorPos(Window, &XPos, &YPos);

        return { static_cast<float>(XPos), static_cast<float>(YPos) };
    }

    bool WindowsInput::GetGamepadButtonDown_Implementation(GamepadID InGamepadID, GamepadButton InGamepadButton)
    {
        GLFWgamepadstate GamepadState;
        if (glfwGetGamepadState(InGamepadID.GetValue(), &GamepadState))
            return GamepadState.buttons[InGamepadButton.GetValue()];

        return false;
    }

    float WindowsInput::GetGamepadAxis_Implementation(GamepadID InGamepadID, GamepadAxis InGamepadAxis)
    {
        GLFWgamepadstate GamepadState;
        if (glfwGetGamepadState(InGamepadID.GetValue(), &GamepadState))
            return GamepadState.axes[InGamepadAxis.GetValue()];

        return -2.0f;
    }
}
