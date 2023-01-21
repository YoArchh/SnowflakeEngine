#include <iostream>

#include "Application/ApplicationEntryPoint.h"

namespace Snowflake
{
    class SnowflakeEditorLayer : public Layer
    {
    public:
        SnowflakeEditorLayer()
            : Layer("Snowflake Editor") {}

        void OnAttach() override
        {
            CLIENT_LOG_INFO("Hello from '{}' Layer!", m_Name);
        }
    };
    
    class SnowflakeEditorApp : public Application
    {
    public:
        SnowflakeEditorApp(const ApplicationSpecification& AppSpecification)
            : Application(AppSpecification) {}

        void OnInitialize() override
        {
            PushLayer(new SnowflakeEditorLayer());
        }
    };

    Application* CreateApplication(ApplicationCommandLineArguments CommandLineArguments)
    {
        ApplicationSpecification SnowflakeEditorAppSpecification;
        SnowflakeEditorAppSpecification.Name = "Snowflake Editor";
        SnowflakeEditorAppSpecification.CommandLineArguments = CommandLineArguments;
        
        return new SnowflakeEditorApp(SnowflakeEditorAppSpecification);
    }
}