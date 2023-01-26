#include "SnowflakePCH.h"
#include "WindowsWindow.h"

#include "Events/KeyboardEvent.h"
#include "Events/MouseEvent.h"
#include "Events/ApplicationEvent.h"
#include "Events/GamepadEvent.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stb_image.h>

namespace Snowflake
{
    GLFWwindow* WindowsWindow::m_WindowHandle = nullptr;
    
    static bool bIsGLFWInitialized = false;
    
    WindowsWindow::WindowsWindow(const WindowSpecification& Specification)
        : m_Specification(Specification) {}

    WindowsWindow::~WindowsWindow()
    {
        glfwDestroyWindow(m_WindowHandle);
        glfwTerminate();
        
        bIsGLFWInitialized = false;
    }

    void WindowsWindow::Initialize()
    {
        m_WindowData.Title = m_Specification.Title;
        m_WindowData.Width = m_Specification.Width;
        m_WindowData.Height = m_Specification.Height;
        m_WindowData.bIsDecorated = m_Specification.bIsDecorated;
        m_WindowData.bIsResizable = m_Specification.bIsResizable;
        m_WindowData.bIsFullscreen = m_Specification.bIsFullscreen;
        m_WindowData.bVSync = m_Specification.bEnableVSync;
        
        ENGINE_LOG_INFO_TAG("Core", "Creating window '{}' (Width: {}, Height: {})", m_Specification.Title, m_Specification.Width, m_Specification.Height);
        
        if (!bIsGLFWInitialized)
        {
            int GLFWInitSuccess = glfwInit();
            ENGINE_ASSERT(GLFWInitSuccess, "Failed to create window '" + m_Specification.Title + "'! Failed to intiailize GLFW!");

            glfwSetErrorCallback([](int ErrorCode, const char* ErrorMessage)
            {
                ENGINE_LOG_ERROR_TAG("GLFW", "A GLFW error occurred: {} (Error Code: {})", ErrorMessage, ErrorCode);
            });
            
            bIsGLFWInitialized = true;
        }

        glfwDefaultWindowHints();

        if (!m_Specification.bIsDecorated)
            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);

        if (m_Specification.bIsFullscreen)
        {
            GLFWmonitor* PrimaryMonitor = glfwGetPrimaryMonitor();
            const GLFWvidmode* VideoMode = glfwGetVideoMode(PrimaryMonitor);

            glfwWindowHint(GLFW_DECORATED, GLFW_FALSE);
            glfwWindowHint(GLFW_RED_BITS, VideoMode->redBits);
            glfwWindowHint(GLFW_GREEN_BITS, VideoMode->greenBits);
            glfwWindowHint(GLFW_BLUE_BITS, VideoMode->blueBits);
            glfwWindowHint(GLFW_REFRESH_RATE, VideoMode->refreshRate);

            m_WindowHandle = glfwCreateWindow(VideoMode->width, VideoMode->height, m_WindowData.Title.c_str(), PrimaryMonitor, nullptr);
        }
        else
        {
            m_WindowHandle = glfwCreateWindow(static_cast<int>(m_Specification.Width), static_cast<int>(m_Specification.Height),
                m_WindowData.Title.c_str(), nullptr, nullptr);
        }

        m_RendererContext = RendererContext::CreateContext(m_WindowHandle);
        m_RendererContext->Initialize();
        
        SetVSync(m_Specification.bEnableVSync);
        
        glfwSetWindowUserPointer(m_WindowHandle, &m_WindowData);

        // Enable raw mouse motion if it is supported
        if (glfwRawMouseMotionSupported())
            glfwSetInputMode(m_WindowHandle, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
        else
            ENGINE_LOG_WARN_TAG("GLFW", "Failed to enable raw mouse motion. It is not supported on the current platform.");

        // Update window size
        {
            int WindowWidth, WindowHeight;
            glfwGetWindowSize(m_WindowHandle, &WindowWidth, &WindowHeight);

            m_WindowData.Width = WindowWidth;
            m_WindowData.Height = WindowHeight;
        }
        
        // Set window icon
        {
            int Channels;
            
            GLFWimage WindowIcon;
            WindowIcon.pixels = stbi_load("Resources/Editor/Snowflake Icon.png", &WindowIcon.width, &WindowIcon.height, &Channels, 4);
            glfwSetWindowIcon(m_WindowHandle, 1, &WindowIcon);
            
            stbi_image_free(WindowIcon.pixels);
        }

        /*----------------------*/
        /* Set window callbacks */
        /*----------------------*/

        glfwSetKeyCallback(m_WindowHandle, [](GLFWwindow* Window, int Key, int Scancode, int Action, int Modifiers)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));

            switch (Action)
            {
                case GLFW_PRESS:
                {
                    KeyPressedEvent KeyPressed(Key, 0);
                    Data.EventCallback(KeyPressed);
                    break;
                }
                case GLFW_RELEASE:
                {
                    KeyReleasedEvent KeyReleased(Key);
                    Data.EventCallback(KeyReleased);
                    break;
                }
                case GLFW_REPEAT:
                {
                    KeyPressedEvent KeyRepeat(Key, 1);
                    Data.EventCallback(KeyRepeat);
                    break;
                }
            }
        });

        glfwSetMouseButtonCallback(m_WindowHandle, [](GLFWwindow* Window, int MouseButton, int Action, int Modifiers)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));

            switch (Action)
            {
                case GLFW_PRESS:
                {
                    MouseButtonPressedEvent MouseButtonPressed(MouseButton);
                    Data.EventCallback(MouseButtonPressed);
                    break;
                }
                case GLFW_RELEASE:
                {
                    MouseButtonReleasedEvent MouseButtonReleased(MouseButton);
                    Data.EventCallback(MouseButtonReleased);
                    break;
                }
            }
        });

        glfwSetScrollCallback(m_WindowHandle, [](GLFWwindow* Window, double XOffset, double YOffset)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));

            MouseScrolledEvent MouseScrolled(static_cast<float>(XOffset), static_cast<float>(YOffset));
            Data.EventCallback(MouseScrolled);
        });

        glfwSetCursorPosCallback(m_WindowHandle, [](GLFWwindow* Window, double XPosition, double YPosition)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            
            MouseMovedEvent MouseMoved(static_cast<float>(XPosition), static_cast<float>(YPosition));
            Data.EventCallback(MouseMoved);
        });

        glfwSetJoystickCallback(WindowsWindow::JoystickCallback);
        
        glfwSetWindowCloseCallback(m_WindowHandle, [](GLFWwindow* Window)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));

            WindowCloseEvent WindowClose(Data.Title);
            Data.EventCallback(WindowClose);
        });

        glfwSetWindowSizeCallback(m_WindowHandle, [](GLFWwindow* Window, int NewWidth, int NewHeight)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));
            Data.Width = NewWidth;
            Data.Height = NewHeight;

            WindowResizeEvent WindowResize(NewWidth, NewHeight);
            Data.EventCallback(WindowResize);
        });

        glfwSetWindowIconifyCallback(m_WindowHandle, [](GLFWwindow* Window, int Iconified)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));

            WindowMinimizeEvent WindowMinimize(Data.Title, static_cast<bool>(Iconified));
            Data.EventCallback(WindowMinimize);
        });

        glfwSetWindowFocusCallback(m_WindowHandle, [](GLFWwindow* Window, int Focused)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));

            switch (Focused)
            {
                case GLFW_TRUE:
                {
                    WindowFocusEvent WindowFocus(static_cast<bool>(Focused));
                    Data.EventCallback(WindowFocus);
                    break;
                }
                case GLFW_FALSE:
                {
                    WindowLostFocusEvent WindowLostFocus(static_cast<bool>(Focused));
                    Data.EventCallback(WindowLostFocus);
                    break;
                }
            }
        });

        glfwSetWindowPosCallback(m_WindowHandle, [](GLFWwindow* Window, int XPosition, int YPosition)
        {
            auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(Window));

            WindowMovedEvent WindowMoved(XPosition, YPosition);
            Data.EventCallback(WindowMoved);
        });
    }

    void WindowsWindow::ProcessEvents()
    {
        glfwPollEvents();
    }

    void WindowsWindow::SwapBuffers()
    {
        m_RendererContext->SwapBuffers();
    }

    Pair<float, float> WindowsWindow::GetPosition() const
    {
        int XPos, YPos;
        glfwGetWindowPos(m_WindowHandle, &XPos, &YPos);

        return { static_cast<float>(XPos), static_cast<float>(YPos) };
    }

    void WindowsWindow::Maximize()
    {
        glfwMaximizeWindow(m_WindowHandle);
    }

    void WindowsWindow::CenterWindow()
    {
        const GLFWvidmode* VideoMode = glfwGetVideoMode(glfwGetPrimaryMonitor());
        int CenterXPos = VideoMode->width / 2 - m_WindowData.Width / 2;
        int CenterYPos = VideoMode->height / 2 - m_WindowData.Height / 2;

        glfwSetWindowPos(m_WindowHandle, CenterXPos, CenterYPos);
    }

    void WindowsWindow::SetVSync(bool bEnabled)
    {
        glfwSwapInterval(bEnabled ? GLFW_TRUE : GLFW_FALSE);

        m_WindowData.bVSync = bEnabled;
    }

    void WindowsWindow::SetResizable(bool bEnabled)
    {
        glfwSetWindowAttrib(m_WindowHandle, GLFW_REPEAT, bEnabled ? GLFW_TRUE : GLFW_FALSE);

        m_WindowData.bIsResizable = bEnabled;
    }

    void WindowsWindow::SetTitle(const std::string& Title)
    {
        glfwSetWindowTitle(m_WindowHandle, Title.c_str());
        
        m_WindowData.Title = Title;
    }

    void WindowsWindow::JoystickCallback(int JoystickID, int Event)
    {
        auto& Data = *static_cast<WindowData*>(glfwGetWindowUserPointer(m_WindowHandle));

        switch (Event)
        {
            case GLFW_CONNECTED:
            {
                GamepadConnectedEvent GamepadConnected(glfwGetGamepadName(JoystickID), JoystickID);
                Data.EventCallback(GamepadConnected);
                break;
            }
            case GLFW_DISCONNECTED:
            {
                GamepadDisconnectedEvent GamepadDisconnected(JoystickID);
                Data.EventCallback(GamepadDisconnected);
                break;
            }
        }
    }
}
