#pragma once

#include "Events/Event.h"

#include "Utils/Pair.h"

#ifdef SNOWFLAKE_PLATFORM_WIN64
    #undef CreateWindow
#endif

namespace Snowflake
{
    struct WindowSpecification
    {
        std::string Title = "Snowflake Engine";
        uint32_t Width = 1600;
        uint32_t Height = 900;
        bool bIsDecorated = true;
        bool bIsResizable = true;
        bool bIsFullscreen = false;
        bool bEnableVSync = true;
    };
    
    class Window
    {
    public:
        using EventCallbackFunction = std::function<void(Event&)>;

        virtual ~Window() = default;

        virtual void Initialize() = 0;
        virtual void ProcessEvents() = 0;
        virtual void SwapBuffers() = 0;

        virtual uint32_t GetWidth() const = 0;
        virtual uint32_t GetHeight() const = 0;

        virtual Pair<uint32_t, uint32_t> GetSize() const = 0;
        virtual Pair<float, float> GetPosition() const = 0;

        virtual void Maximize() = 0;
        virtual void CenterWindow() = 0;

        virtual void SetEventCallbackFunction(const EventCallbackFunction& CallbackFunc) = 0;

        virtual void SetVSync(bool bEnabled) = 0;
        virtual bool IsVSyncEnabled() = 0;

        virtual bool IsResizable() const = 0;
        virtual void SetResizable(bool bEnabled) = 0;
        
        virtual const std::string& GetTitle() const = 0;
        virtual void SetTitle(const std::string& Title) = 0;

        virtual void* GetHandle() const = 0;

        static Scope<Window> CreateWindow(const WindowSpecification& Specification = WindowSpecification());
    };
}
