#pragma once

namespace Snowflake
{
    /*-----------------------------*/
    /* -- Base Key Code Structs -- */
    /*-----------------------------*/
    
    struct Key
    {
        Key(const std::string& Name, uint16_t Value)
            : m_Name(Name), m_Value(Value) {}

        std::string GetName() const { return m_Name; }
        uint16_t GetValue() const { return m_Value; }
        
    private:
        std::string m_Name;
        uint16_t m_Value;
    };

    struct MouseButton
    {
        MouseButton(const std::string& Name, uint16_t Value)
            : m_Name(Name), m_Value(Value) {}

        std::string GetName() const { return m_Name; }
        uint16_t GetValue() const { return m_Value; }
        
    private:
        std::string m_Name;
        uint16_t m_Value;
    };

    struct GamepadID
    {
        GamepadID(const std::string& Name, uint16_t Value)
            : m_Name(Name), m_Value(Value) {}

        std::string GetName() const { return m_Name; }
        uint16_t GetValue() const { return m_Value; }
        
    private:
        std::string m_Name;
        uint16_t m_Value;
    };

    struct GamepadButton
    {
        GamepadButton(const std::string& Name, uint16_t Value)
            : m_Name(Name), m_Value(Value) {}

        std::string GetName() const { return m_Name; }
        uint16_t GetValue() const { return m_Value; }
        
    private:
        std::string m_Name;
        uint16_t m_Value;
    };

    struct GamepadAxis
    {
        GamepadAxis(const std::string& Name, uint16_t Value)
            : m_Name(Name), m_Value(Value) {}

        std::string GetName() const { return m_Name; }
        uint16_t GetValue() const { return m_Value; }
        
    private:
        std::string m_Name;
        uint16_t m_Value;
    };
}

// Include an implementation header for the key codes depending on the platform.
#ifdef SNOWFLAKE_PLATFORM_WIN64
    #include "Windows/WindowsKeys.h"
#else
    #error "Failed to initialize key codes! Unknown/unsupported platform!"
#endif
