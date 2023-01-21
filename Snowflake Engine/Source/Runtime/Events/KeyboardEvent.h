#pragma once

#include "Event.h"

#include <sstream>

namespace Snowflake
{
    class KeyboardEvent : public Event
    {
    public:
        inline uint16_t GetKeyCode() const { return m_KeyCode; }

        EVENT_CLASS_CATEGORY(KeyboardEventCategory | InputEventCategory)
        
    protected:
        KeyboardEvent(uint16_t KeyCode)
            : m_KeyCode(KeyCode) {}

        uint16_t m_KeyCode;
    };

    class KeyPressedEvent : public KeyboardEvent
    {
    public:
        KeyPressedEvent(uint16_t KeyCode, int RepeatCount)
            : KeyboardEvent(KeyCode), m_RepeatCount(RepeatCount) {}

        inline int GetRepeatCount() const { return m_RepeatCount; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "KeyPressedEvent: " << m_KeyCode << " (Repeats: " << m_RepeatCount << ")";
            return 0;
        }

        EVENT_CLASS_TYPE(KeyPressed)
        
    private:
        int m_RepeatCount;
    };

    class KeyReleasedEvent : public KeyboardEvent
    {
    public:
        KeyReleasedEvent(uint16_t KeyCode)
            : KeyboardEvent(KeyCode) {}

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "KeyReleasedEvent: " << m_KeyCode;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(KeyReleased)
    };

    class KeyTypedEvent : public KeyboardEvent
    {
    public:
        KeyTypedEvent(uint16_t KeyCode)
            : KeyboardEvent(KeyCode) {}

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "KeyTypedEvent: " << m_KeyCode;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(KeyTyped)
    };
}