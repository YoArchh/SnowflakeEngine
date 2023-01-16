#pragma once

#include "Application/Application.h"

extern Snowflake::Application* Snowflake::CreateApplication(ApplicationCommandLineArguments CommandLineArguments);

namespace Snowflake
{
    int Main(int ArgsCount, char** Args)
    {
        Application* App = CreateApplication({ ArgsCount, Args });
        App->Start();
        delete App;
        
        return 0;
    }
}

int main(int argc, char** argv)
{
    return Snowflake::Main(argc, argv);
}