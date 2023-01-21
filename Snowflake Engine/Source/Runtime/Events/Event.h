#pragma once

#include <functional>
#include <ostream>

namespace Snowflake
{
    enum class EventType
    {
        None = 0,

        KeyPressed, KeyReleased, KeyTyped,
        MouseButtonPressed, MouseButtonReleased, MouseScrolled, MouseMoved,
        WindowClose, WindowMinimize, WindowResize, WindowFocus, WindowLostFocus, WindowMoved,
        ApplicationUpdate, ApplicationRender, ApplicationTick
    };

    enum EventCategory
    {
        None = 0,

        ApplicationEventCategory = 1u << 0,
        InputEventCategory = 1u << 1,
        KeyboardEventCategory = 1u << 2,
        MouseEventCategory = 1u << 3,
        MouseButtonEventCategory = 1u << 4
    };

#define EVENT_CLASS_TYPE(type) static EventType GetStaticType() { return EventType::##type; }\
                               virtual EventType GetEventType() const override { return GetStaticType(); }\
                               virtual const char* GetName() const override { return #type; }

#define EVENT_CLASS_CATEGORY(category) virtual int GetCategoryFlags() const override { return EventCategory::##category; }

    class Event
    {
    public:
        virtual ~Event() = default;

        virtual EventType GetEventType() const = 0;
        virtual const char* GetName() const = 0;
        virtual int GetCategoryFlags() const = 0;
        virtual std::string ToString() const { return GetName(); }

        inline bool IsInCategory(EventCategory Category)
        {
            return GetCategoryFlags() & Category;
        }

    public:
        bool bHandled = false;
    };

    class EventDispatcher
    {
    private:
        template<typename T>
        using EventFunction = std::function<bool(T&)>;

    public:
        EventDispatcher(Event& InEvent)
            : m_Event(InEvent) {}

        template<typename T>
        bool Dispatch(EventFunction<T> EventFunc)
        {
            if (m_Event.GetEventType() == T::GetStaticType() && !m_Event.bHandled)
            {
                m_Event.bHandled = EventFunc(*static_cast<T*>(&m_Event));
                return true;
            }

            return false;
        }

    private:
        Event& m_Event;
    };
}