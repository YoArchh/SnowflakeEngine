#pragma once

#include "Application/Window.h"

struct GLFWwindow;

namespace Snowflake
{
    class WindowsWindow : public Window
    {
    public:
        WindowsWindow(const WindowSpecification& Specification);
        virtual ~WindowsWindow();

        virtual void Initialize() override;
        virtual void ProcessEvents() override;
        virtual void SwapBuffers() override;

        inline uint32_t GetWidth() const override { return m_WindowData.Width; }
        inline uint32_t GetHeight() const override { return m_WindowData.Height; }

        virtual Pair<uint32_t, uint32_t> GetSize() const override { return { m_WindowData.Width, m_WindowData.Height }; }
        virtual Pair<float, float> GetPosition() const override;

        virtual void Maximize() override;
        virtual void CenterWindow() override;

        virtual void SetEventCallbackFunction(const EventCallbackFunction& CallbackFunc) override { m_WindowData.EventCallback = CallbackFunc; }

        virtual void SetVSync(bool bEnabled) override;
        virtual bool IsVSyncEnabled() override { return m_WindowData.bVSync; }

        virtual bool IsResizable() const override { return m_WindowData.bIsResizable; }
        virtual void SetResizable(bool bEnabled) override;

        virtual const std::string& GetTitle() const override { return m_WindowData.Title; }
        virtual void SetTitle(const std::string& Title) override;

        inline void* GetHandle() const override { return m_WindowHandle; }

    private:
        static void JoystickCallback(int JoystickID, int Event);
        
    private:
        struct WindowData
        {
            std::string Title = "Snowflake Engine";
            uint32_t Width = 1600;
            uint32_t Height = 900;
            bool bIsDecorated = true;
            bool bIsResizable = true;
            bool bIsFullscreen = false;
            bool bVSync = true;

            EventCallbackFunction EventCallback;
        };
        
        static GLFWwindow* m_WindowHandle;
        WindowSpecification m_Specification;
        WindowData m_WindowData;
    };

}