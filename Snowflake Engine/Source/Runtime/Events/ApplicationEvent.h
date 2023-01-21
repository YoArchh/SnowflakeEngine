#pragma once

#include "Event.h"

#include <sstream>

namespace Snowflake
{
    class WindowCloseEvent : public Event
    {
    public:
        WindowCloseEvent(const std::string& WindowTitle)
            : m_WindowTitle(WindowTitle) {}

        inline std::string GetWindowTitle() const { return m_WindowTitle; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "WindowCloseEvent: " << m_WindowTitle;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(WindowClose)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
        
    private:
        std::string m_WindowTitle;
    };

    class WindowMinimizeEvent : public Event
    {
    public:
       WindowMinimizeEvent(const std::string& WindowTitle, bool bIsWindowMinimized)
           : m_WindowTitle(WindowTitle), bIsMinimized(bIsWindowMinimized) {}

        inline std::string GetWindowTitle() const { return m_WindowTitle; }
        inline bool IsWindowMinimized() const { return bIsMinimized; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "WindowMinimizeEvent: " << m_WindowTitle;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(WindowMinimize)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
        
    private:
        std::string m_WindowTitle;
        bool bIsMinimized;
    };

    class WindowResizeEvent : public Event
    {
    public:
        WindowResizeEvent(int WindowWidth, int WindowHeight)
            : m_WindowWidth(WindowWidth), m_WindowHeight(WindowHeight) {}

        inline int GetWindowWidth() const { return m_WindowWidth; }
        inline int GetWindowHeight() const { return m_WindowHeight; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "WindowResizeEvent (Width: " << m_WindowWidth << ", Height: " << m_WindowHeight << ")";
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(WindowResize)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
        
    private:
        int m_WindowWidth, m_WindowHeight;
    };

    class WindowFocusEvent : public Event
    {
    public:
        WindowFocusEvent(bool bIsWindowFocused)
            : bIsFocused(bIsWindowFocused) {}

        inline bool IsWindowFocused() const { return bIsFocused; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "WindowFocusEvent: " << (bIsFocused ? "True" : "False");
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(WindowFocus)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
        
    private:
        bool bIsFocused;
    };

    class WindowLostFocusEvent : public Event
    {
    public:
        WindowLostFocusEvent(bool bIsWindowFocusLost)
            : bIsFocusLost(bIsWindowFocusLost) {}

        inline bool IsWindowFocusLost() const { return bIsFocusLost; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "WindowLostFocusEvent: " << (bIsFocusLost ? "True" : "False");
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(WindowLostFocus)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
        
    private:
        bool bIsFocusLost;
    };

    class WindowMovedEvent : public Event
    {
    public:
        WindowMovedEvent(int XPosition, int YPosition)
            : m_XPosition(XPosition), m_YPosition(YPosition) {}

        inline int GetXPosition() const { return m_XPosition; }
        inline int GetYPosition() const { return m_YPosition; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "WindowMovedEvent (X: " << m_XPosition << ", Y: " << m_YPosition << ")";
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(WindowMoved)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
        
    private:
        int m_XPosition, m_YPosition;
    };

    /*-------------------------------------------------------------------------------------*/
    /* -- TODO: Maybe take in an instance to an Appliction in the constructors instead? -- */
    /*-------------------------------------------------------------------------------------*/

    class ApplicationUpdateEvent : public Event
    {
    public:
        ApplicationUpdateEvent(const std::string& ApplicationName)
            : m_ApplicationName(ApplicationName) {}

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "ApplicationUpdateEvent: " << m_ApplicationName;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(ApplicationUpdate)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    private:
        std::string m_ApplicationName;
    };

    class ApplicationRenderEvent : public Event
    {
    public:
        ApplicationRenderEvent(const std::string& ApplicationName)
            : m_ApplicationName(ApplicationName) {}

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "ApplicationRenderEvent: " << m_ApplicationName;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(ApplicationRender)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    private:
        std::string m_ApplicationName;
    };

    class ApplicationTickEvent : public Event
    {
    public:
        ApplicationTickEvent(const std::string& ApplicationName)
            : m_ApplicationName(ApplicationName) {}

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "ApplicationTickEvent: " << m_ApplicationName;
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(ApplicationTick)
        EVENT_CLASS_CATEGORY(ApplicationEventCategory)
    private:
        std::string m_ApplicationName;
    };
}