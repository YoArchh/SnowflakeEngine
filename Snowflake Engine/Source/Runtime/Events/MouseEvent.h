#pragma once

#include "Event.h"

#include <sstream>

namespace Snowflake
{
    class MouseButtonEvent : public Event
    {
    public:
        inline int GetMouseButton() const { return m_MouseButton; }

        EVENT_CLASS_CATEGORY(MouseButtonEventCategory | MouseEventCategory | InputEventCategory)
        
    protected:
        MouseButtonEvent(uint16_t MouseButton)
            : m_MouseButton(MouseButton) {}
        
        uint16_t m_MouseButton;
    };

    class MouseButtonPressedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonPressedEvent(uint16_t MouseButton)
            : MouseButtonEvent(MouseButton) {}

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "MouseButtonPressedEvent: " << m_MouseButton;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(MouseButtonPressed)
    };

    class MouseButtonReleasedEvent : public MouseButtonEvent
    {
    public:
        MouseButtonReleasedEvent(uint16_t MouseButton)
            : MouseButtonEvent(MouseButton) {}

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "MouseButtonReleasedEvent: " << m_MouseButton;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(MouseButtonReleased)
    };

    class MouseScrolledEvent : public Event
    {
    public:
        MouseScrolledEvent(float XOffset, float YOffset)
            : m_XOffset(XOffset), m_YOffset(YOffset) {}

        inline float GetXOffset() const { return m_XOffset; }
        inline float GetYOffset() const { return m_YOffset; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "MouseScrolledEvent (X: " << m_XOffset << ", Y: " << m_YOffset << ")";
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(MouseScrolled)
        EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory)
    private:
        float m_XOffset, m_YOffset;
    };

    class MouseMovedEvent : public Event
    {
    public:
        MouseMovedEvent(float XPosition, float YPosition)
            : m_XPosition(XPosition), m_YPosition(YPosition) {}

        inline float GetXPosition() const { return m_XPosition; }
        inline float GetYPosition() const { return m_YPosition; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "MouseMovedEvent (X: " << m_XPosition << ", Y: " << m_YPosition << ")";
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(MouseMoved)
        EVENT_CLASS_CATEGORY(MouseEventCategory | InputEventCategory)
    private:
        float m_XPosition, m_YPosition;
    };
}