#pragma once

#include "Event.h"

#include <sstream>

namespace Snowflake
{
    class GamepadConnectedEvent : public Event
    {
    public:
        GamepadConnectedEvent(const std::string& GamepadName, int GamepadID)
            : m_GamepadName(GamepadName), m_GamepadID(GamepadID) {}

        std::string GetGamepadName() const { return m_GamepadName; }
        int GetGamepadID() const { return m_GamepadID; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "GamepadConnectedEvent: " << m_GamepadName << " (ID: " << m_GamepadID << ")";
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(GamepadConnected)
        EVENT_CLASS_CATEGORY(GamepadEventCategory)
        
    private:
        std::string m_GamepadName;
        int m_GamepadID;
    };

    class GamepadDisconnectedEvent : public Event
    {
    public:
        GamepadDisconnectedEvent(int GamepadID)
            : m_GamepadID(GamepadID) {}

        int GetGamepadID() const { return m_GamepadID; }

        std::string ToString() const override
        {
            std::stringstream StringStream;
            StringStream << "GamepadDisconnectedEvent (ID: " << m_GamepadID << ")";
            return StringStream.str();
        }

        EVENT_CLASS_TYPE(GamepadDisconnected)
        EVENT_CLASS_CATEGORY(GamepadEventCategory)
        
    private:
        int m_GamepadID;
    };
}