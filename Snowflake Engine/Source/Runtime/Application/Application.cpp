#include "SnowflakePCH.h"
#include "Application.h"

#include "Logging/Logger.h"

#include "Events/ApplicationEvent.h"

extern bool bIsApplicationRunning;

namespace Snowflake
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& AppSpecification)
        : m_Specification(AppSpecification)
    {
        s_Instance = this;
        
        LoggingSystem::Initialize();

        ENGINE_LOG_INFO("Welcome to Snowflake Engine!");

        // Event System Test
        WindowResizeEvent ResizeEvent(1600, 900);
        ENGINE_LOG_INFO_TAG("Event", ResizeEvent.ToString());

        ApplicationUpdateEvent AppUpdateEvent(AppSpecification.Name);
        CLIENT_LOG_INFO_TAG("Event", AppUpdateEvent.ToString());
    }

    Application::~Application()
    {
        LoggingSystem::Shutdown();
    }

    void Application::Start()
    {
        OnInitialize();
        
        while (bIsRunning)
        {
            DispatchEvent<ApplicationUpdateEvent, true>(m_Specification.Name);
            
            ProcessEvents();

            DispatchEvent<ApplicationTickEvent, true>(m_Specification.Name);
        }

        OnShutdown();
    }

    void Application::Restart()
    {
        bIsRunning = false;
    }

    void Application::Close()
    {
        bIsRunning = false;
        bIsApplicationRunning = false;
    }

    void Application::OnShutdown()
    {
        m_EventCallbacks.clear();
    }

    void Application::OnEvent(Event& InEvent)
    {
        EventDispatcher Dispatcher(InEvent);

        for (auto& EventCallback : m_EventCallbacks)
        {
            EventCallback(InEvent);

            if (InEvent.bHandled)
                break;
        }
    }

    void Application::ProcessEvents()
    {
        // Template arguments are deduced automatically, no need to write them explicitly.
        std::scoped_lock Lock(m_EventQueueMutex);

        while (!m_EventQueue.empty())
        {
            auto& EventFunction = m_EventQueue.front();
            EventFunction();

            m_EventQueue.pop();
        }
    }
}
