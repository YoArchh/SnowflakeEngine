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

        m_ApplicationWindow = Window::CreateWindow();
        m_ApplicationWindow->Initialize();
        m_ApplicationWindow->SetEventCallbackFunction([this](Event& InEvent) { OnEvent(InEvent); });
        m_ApplicationWindow->CenterWindow();
    }

    Application::~Application()
    {
        m_ApplicationWindow->SetEventCallbackFunction([](Event&) {});
        
        LoggingSystem::Shutdown();
    }

    void Application::Start()
    {
        OnInitialize();
        
        while (bIsRunning)
        {
            DispatchEvent<ApplicationUpdateEvent>(m_Specification.Name);
            
            ProcessEvents();

            if (!bIsWindowMinimized)
            {
                m_ApplicationWindow->SwapBuffers();
            }
            
            DispatchEvent<ApplicationTickEvent>(m_Specification.Name);
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
        Dispatcher.Dispatch<WindowCloseEvent>([this](WindowCloseEvent& Event) { return OnWindowClose(Event); });
        Dispatcher.Dispatch<WindowMinimizeEvent>([this](WindowMinimizeEvent& Event) { return OnWindowMinimize(Event); });
        
        for (auto& EventCallback : m_EventCallbacks)
        {
            if (InEvent.bHandled)
                continue;
            
            EventCallback(InEvent);
        }
    }

    bool Application::OnWindowClose(WindowCloseEvent& Event)
    {
        Close();

        return true;
    }

    bool Application::OnWindowMinimize(WindowMinimizeEvent& Event)
    {
        bIsWindowMinimized = Event.IsWindowMinimized();

        return true;
    }

    void Application::ProcessEvents()
    {
        m_ApplicationWindow->ProcessEvents();
        
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
