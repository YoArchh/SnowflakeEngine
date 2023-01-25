#pragma once

#ifdef SNOWFLAKE_PLATFORM_WIN64
    #include <GLFW/glfw3.h>
#endif

namespace Snowflake
{
    
    /*-----------------------------------------------*/
    /* -- Windows Key Code Implementation Structs -- */
    /*-----------------------------------------------*/

    // TODO: (YoArchh) Complete.
    struct Keys
    {
        inline static const Key Space = Key("Space", GLFW_KEY_SPACE);
        inline static const Key Apostrophe = Key("Apostrophe", GLFW_KEY_APOSTROPHE);
        inline static const Key Comma = Key("Comma", GLFW_KEY_COMMA);
        inline static const Key Minus = Key("Minus", GLFW_KEY_MINUS);
        inline static const Key Period = Key("Period", GLFW_KEY_PERIOD);
        inline static const Key Slash = Key("Slash", GLFW_KEY_SLASH);

        inline static const Key Zero = Key("Zero", GLFW_KEY_0);
        inline static const Key One = Key("One", GLFW_KEY_1);
        inline static const Key Two = Key("Two", GLFW_KEY_2);
        inline static const Key Three = Key("Three", GLFW_KEY_3);
        inline static const Key Four = Key("Four", GLFW_KEY_4);
        inline static const Key Five = Key("Five", GLFW_KEY_5);
        inline static const Key Six = Key("Six", GLFW_KEY_6);
        inline static const Key Seven = Key("Seven", GLFW_KEY_7);
        inline static const Key Eight = Key("Eight", GLFW_KEY_8);
        inline static const Key Nine = Key("Nine", GLFW_KEY_9);

        inline static const Key Semicolon = Key("Semicolon", GLFW_KEY_SEMICOLON);
        inline static const Key Equal = Key("Equal", GLFW_KEY_EQUAL);

        inline static const Key A = Key("A", GLFW_KEY_A);
        inline static const Key B = Key("B", GLFW_KEY_B);
        inline static const Key C = Key("C", GLFW_KEY_C);
        inline static const Key D = Key("D", GLFW_KEY_D);
        inline static const Key E = Key("E", GLFW_KEY_E);
        inline static const Key F = Key("F", GLFW_KEY_F);
        inline static const Key G = Key("G", GLFW_KEY_G);
        inline static const Key H = Key("H", GLFW_KEY_H);
        inline static const Key I = Key("I", GLFW_KEY_I);
        inline static const Key J = Key("J", GLFW_KEY_J);
        inline static const Key K = Key("K", GLFW_KEY_K);
        inline static const Key L = Key("L", GLFW_KEY_L);
        inline static const Key M = Key("M", GLFW_KEY_M);
        inline static const Key N = Key("N", GLFW_KEY_N);
        inline static const Key O = Key("O", GLFW_KEY_O);
        inline static const Key P = Key("P", GLFW_KEY_P);
        inline static const Key Q = Key("Q", GLFW_KEY_Q);
        inline static const Key R = Key("R", GLFW_KEY_R);
        inline static const Key S = Key("S", GLFW_KEY_S);
        inline static const Key T = Key("T", GLFW_KEY_T);
        inline static const Key U = Key("U", GLFW_KEY_U);
        inline static const Key V = Key("V", GLFW_KEY_V);
        inline static const Key W = Key("W", GLFW_KEY_W);
        inline static const Key X = Key("X", GLFW_KEY_X);
        inline static const Key Y = Key("Y", GLFW_KEY_Y);
        inline static const Key Z = Key("Z", GLFW_KEY_Z);

        inline static const Key LeftBracket = Key("Left Bracket", GLFW_KEY_LEFT_BRACKET);
        inline static const Key RightBracket = Key("Right Bracket", GLFW_KEY_RIGHT_BRACKET);

        inline static const Key Backslash = Key("Backslash", GLFW_KEY_BACKSLASH);
        inline static const Key GraveAccent = Key("Grave Accent", GLFW_KEY_GRAVE_ACCENT);

        inline static const Key WorldOne = Key("World One", GLFW_KEY_WORLD_1);
        inline static const Key WorldTwo = Key("World Two", GLFW_KEY_WORLD_2);

        inline static const Key Escape = Key("Escape", GLFW_KEY_ESCAPE);
        inline static const Key Enter = Key("Enter", GLFW_KEY_ENTER);
        inline static const Key Tab = Key("Tab", GLFW_KEY_TAB);
        inline static const Key Backspace = Key("Backspace", GLFW_KEY_BACKSPACE);
        inline static const Key Insert = Key("Insert", GLFW_KEY_INSERT);
        inline static const Key Delete = Key("Delete", GLFW_KEY_DELETE);

        inline static const Key RightArrow = Key("Right Arrow", GLFW_KEY_RIGHT);
        inline static const Key LeftArrow = Key("Left Arrow", GLFW_KEY_LEFT);
        inline static const Key DownArrow = Key("Down Arrow", GLFW_KEY_DOWN);
        inline static const Key UpArrow = Key("Up Arrow", GLFW_KEY_UP);

        inline static const Key PageUp = Key("Page Up", GLFW_KEY_PAGE_UP);
        inline static const Key PageDown = Key("Page Down", GLFW_KEY_PAGE_DOWN);

        inline static const Key Home = Key("Home", GLFW_KEY_HOME);
        inline static const Key End = Key("End", GLFW_KEY_END);
        inline static const Key CapsLock = Key("Caps Lock", GLFW_KEY_CAPS_LOCK);
        inline static const Key ScrollLock = Key("Scroll Lock", GLFW_KEY_SCROLL_LOCK);
        inline static const Key NumberLock = Key("Number Lock", GLFW_KEY_NUM_LOCK);
        inline static const Key PrintScreen = Key("Print Screen", GLFW_KEY_PRINT_SCREEN);
        inline static const Key Pause = Key("Pause", GLFW_KEY_PAUSE);

        inline static const Key F1 = Key("F1", GLFW_KEY_F1);
        inline static const Key F2 = Key("F2", GLFW_KEY_F2);
        inline static const Key F3 = Key("F3", GLFW_KEY_F3);
        inline static const Key F4 = Key("F4", GLFW_KEY_F4);
        inline static const Key F5 = Key("F5", GLFW_KEY_F5);
        inline static const Key F6 = Key("F6", GLFW_KEY_F6);
        inline static const Key F7 = Key("F7", GLFW_KEY_F7);
        inline static const Key F8 = Key("F8", GLFW_KEY_F8);
        inline static const Key F9 = Key("F9", GLFW_KEY_F9);
        inline static const Key F10 = Key("F10", GLFW_KEY_F10);
        inline static const Key F11 = Key("F11", GLFW_KEY_F11);
        inline static const Key F12 = Key("F12", GLFW_KEY_F12);
        inline static const Key F13 = Key("F13", GLFW_KEY_F13);
        inline static const Key F14 = Key("F14", GLFW_KEY_F14);
        inline static const Key F15 = Key("F15", GLFW_KEY_F15);
        inline static const Key F16 = Key("F16", GLFW_KEY_F16);
        inline static const Key F17 = Key("F17", GLFW_KEY_F17);
        inline static const Key F18 = Key("F18", GLFW_KEY_F18);
        inline static const Key F19 = Key("F19", GLFW_KEY_F19);
        inline static const Key F20 = Key("F20", GLFW_KEY_F20);
        inline static const Key F21 = Key("F21", GLFW_KEY_F21);
        inline static const Key F22 = Key("F22", GLFW_KEY_F22);
        inline static const Key F23 = Key("F23", GLFW_KEY_F23);
        inline static const Key F24 = Key("F24", GLFW_KEY_F24);
        inline static const Key F25 = Key("F25", GLFW_KEY_F25);

        inline static const Key KeyPadZero = Key("KeyPad Zero", GLFW_KEY_KP_0);
        inline static const Key KeyPadOne = Key("KeyPad One", GLFW_KEY_KP_1);
        inline static const Key KeyPadTwo = Key("KeyPad Two", GLFW_KEY_KP_2);
        inline static const Key KeyPadThree = Key("KeyPad Three", GLFW_KEY_KP_3);
        inline static const Key KeyPadFour = Key("KeyPad Four", GLFW_KEY_KP_4);
        inline static const Key KeyPadFive = Key("KeyPad Five", GLFW_KEY_KP_5);
        inline static const Key KeyPadSix = Key("KeyPad Six", GLFW_KEY_KP_6);
        inline static const Key KeyPadSeven = Key("KeyPad Seven", GLFW_KEY_KP_7);
        inline static const Key KeyPadEight = Key("KeyPad Eight", GLFW_KEY_KP_8);
        inline static const Key KeyPadNine = Key("KeyPad Nine", GLFW_KEY_KP_9);
        inline static const Key KeyPadDecimal = Key("KeyPad Decimal", GLFW_KEY_KP_DECIMAL);
        inline static const Key KeyPadDivide = Key("KeyPad Divide", GLFW_KEY_KP_DIVIDE);
        inline static const Key KeyPadMultiply = Key("KeyPad Multiply", GLFW_KEY_KP_MULTIPLY);
        inline static const Key KeyPadSubtract = Key("KeyPad Subtract", GLFW_KEY_KP_SUBTRACT);
        inline static const Key KeyPadAdd = Key("KeyPad Add", GLFW_KEY_KP_ADD);
        inline static const Key KeyPadEnter = Key("KeyPad Enter", GLFW_KEY_KP_ENTER);
        inline static const Key KeyPadEqual = Key("KeyPad Equal", GLFW_KEY_KP_EQUAL);

        inline static const Key LeftShift = Key("Left Shift", GLFW_KEY_LEFT_SHIFT);
        inline static const Key LeftControl = Key("Left Control", GLFW_KEY_LEFT_CONTROL);
        inline static const Key LeftAlt = Key("Left Alt", GLFW_KEY_LEFT_ALT);
        inline static const Key LeftSuper = Key("Left Super", GLFW_KEY_LEFT_SUPER);

        inline static const Key RightShift = Key("Right Shift", GLFW_KEY_RIGHT_SHIFT);  
        inline static const Key RightControl = Key("Right Control", GLFW_KEY_RIGHT_CONTROL);
        inline static const Key RightAlt = Key("Right Alt", GLFW_KEY_RIGHT_ALT);        
        inline static const Key RightSuper = Key("Right Super", GLFW_KEY_RIGHT_SUPER);

        inline static const Key Menu = Key("Menu", GLFW_KEY_MENU);
    };

    struct MouseButtons
    {
        inline static const MouseButton MouseButtonOne = MouseButton("Mouse Button One", 0);
        inline static const MouseButton MouseButtonTwo = MouseButton("Mouse Button Two", 1);
        inline static const MouseButton MouseButtonThree = MouseButton("Mouse Button Three", 2);
        inline static const MouseButton MouseButtonFour = MouseButton("Mouse Button Four", 3);
        inline static const MouseButton MouseButtonFive = MouseButton("Mouse Button Five", 4);
        inline static const MouseButton MouseButtonSix = MouseButton("Mouse Button Six", 5);
        inline static const MouseButton MouseButtonSeven = MouseButton("Mouse Button Seven", 6);
        inline static const MouseButton MouseButtonEight = MouseButton("Mouse Button Eight", 7);
        
        inline static const MouseButton LeftMouseButton = MouseButton("Left Mouse Button", MouseButtonOne.GetValue());
        inline static const MouseButton RightMouseButton = MouseButton("Right Mouse Button", MouseButtonTwo.GetValue());
        inline static const MouseButton MiddleMouseButton = MouseButton("Middle Mouse Button", MouseButtonThree.GetValue());
    };

    struct GamepadIDs
    {
        inline static const GamepadID GamepadOne = GamepadID("Gamepad One", 0);
        inline static const GamepadID GamepadTwo = GamepadID("Gamepad Two", 1);
        inline static const GamepadID GamepadThree = GamepadID("Gamepad Three", 2);
        inline static const GamepadID GamepadFour = GamepadID("Gamepad Four", 3);
        inline static const GamepadID GamepadFive = GamepadID("Gamepad Five", 4);
        inline static const GamepadID GamepadSix = GamepadID("Gamepad Six", 5);
        inline static const GamepadID GamepadSeven = GamepadID("Gamepad Seven", 6);
        inline static const GamepadID GamepadEight = GamepadID("Gamepad Eight", 7);
        inline static const GamepadID GamepadNine = GamepadID("Gamepad Nine", 8);
        inline static const GamepadID GamepadTen = GamepadID("Gamepad Ten", 9);
        inline static const GamepadID GamepadEleven = GamepadID("Gamepad Eleven", 10);
        inline static const GamepadID GamepadTwelve = GamepadID("Gamepad Twelve", 11);
        inline static const GamepadID GamepadThirteen = GamepadID("Gamepad Thirteen", 12);
        inline static const GamepadID GamepadFourteen = GamepadID("Gamepad Fourteen", 13);
        inline static const GamepadID GamepadFifteen = GamepadID("Gamepad Fifteen", 14);
        inline static const GamepadID GamepadSixteen = GamepadID("Gamepad Sixteen", 15);
    };

    struct GamepadButtons
    {
        inline static const GamepadButton FaceButtonBottom = GamepadButton("Gamepad Face Button Bottom", 0);
        inline static const GamepadButton FaceButtonRight = GamepadButton("Gamepad Face Button Right", 1);
        inline static const GamepadButton FaceButtonLeft = GamepadButton("Gamepad Face Button Left", 2);
        inline static const GamepadButton FaceButtonTop = GamepadButton("Gamepad Face Button Top", 3);

        inline static const GamepadButton LeftBumper = GamepadButton("Gamepad Left Bumper", 4);
        inline static const GamepadButton RightBumper = GamepadButton("Gamepad Right Bumper", 5);

        inline static const GamepadButton Back = GamepadButton("Gamepad Back", 6);
        inline static const GamepadButton Start = GamepadButton("Gamepad Start", 7);
        inline static const GamepadButton Guide = GamepadButton("Gamepad Guide", 8);

        // Pressing down on either stick
        inline static const GamepadButton LeftThumbstick = GamepadButton("Gamepad Button Left Thumbstick", 9);
        inline static const GamepadButton RightThumbstick = GamepadButton("Gamepad Button Right Thumbstick", 10);

        inline static const GamepadButton DPadUp = GamepadButton("Gamepad DPad Up", 11);
        inline static const GamepadButton DPadRight = GamepadButton("Gamepad DPad Right", 12);
        inline static const GamepadButton DPadDown = GamepadButton("Gamepad DPad Down", 13);
        inline static const GamepadButton DPadLeft = GamepadButton("Gamepad DPad Left", 14);
    };

    struct GamepadAxes
    {
        inline static const GamepadAxis LeftThumbstickX = GamepadAxis("Gamepad Left Thumbstick X", 0);
        inline static const GamepadAxis LeftThumbstickY = GamepadAxis("Gamepad Left Thumbstick Y", 1);

        inline static const GamepadAxis RightThumbstickX = GamepadAxis("Gamepad Right Thumbstick X", 2);
        inline static const GamepadAxis RightThumbstickY = GamepadAxis("Gamepad Right Thumbstick Y", 3);

        inline static const GamepadAxis LeftTrigger = GamepadAxis("Gamepad Left Trigger", 4);
        inline static const GamepadAxis RightTrigger = GamepadAxis("Gamepad Right Trigger", 5);
    };
}
