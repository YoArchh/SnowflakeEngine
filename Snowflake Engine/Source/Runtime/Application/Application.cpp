#include "SnowflakePCH.h"
#include "Application.h"

#include "Logging/Logger.h"

namespace Snowflake
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& AppSpecification)
        : m_Specification(AppSpecification)
    {
        LoggingSystem::Initialize();

        ENGINE_LOG_INFO("Welcome to Snowflake Engine!");
        CLIENT_LOG_DEBUG_TAG("Client Core", "Test Tagged Message (Number: {})", 20.0f);
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
            
        }

        OnShutdown();
    }

    void Application::Close()
    {
        bIsRunning = false;
    }
}
