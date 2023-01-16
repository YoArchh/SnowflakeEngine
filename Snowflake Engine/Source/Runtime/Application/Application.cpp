#include "SnowflakePCH.h"
#include "Application.h"

namespace Snowflake
{
    Application* Application::s_Instance = nullptr;

    Application::Application(const ApplicationSpecification& AppSpecification)
        : m_Specification(AppSpecification) {}

    Application::~Application()
    {
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
