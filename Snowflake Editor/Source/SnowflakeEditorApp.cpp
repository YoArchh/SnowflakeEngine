#include <iostream>

#include "Application/ApplicationEntryPoint.h"

namespace Snowflake
{
    class SnowflakeEditorApp : public Application
    {
    public:
        SnowflakeEditorApp(ApplicationSpecification& AppSpecification)
            : Application(AppSpecification) {}

        void OnInitialize() override
        {
            std::cout << "Welcome to Snowflake Engine!" << std::endl;
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