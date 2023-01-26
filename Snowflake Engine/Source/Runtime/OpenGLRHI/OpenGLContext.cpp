#include "SnowflakePCH.h"
#include "OpenGLContext.h"

#include <GLFW/glfw3.h>
#include <glad/glad.h>

namespace Snowflake
{
    OpenGLContext::OpenGLContext(void* WindowHandle)
        : m_WindowHandle(WindowHandle)
    {
        ENGINE_ASSERT(m_WindowHandle != nullptr, "Failed to create OpenGL context! Window handle is invalid!")
    }

    void OpenGLContext::Initialize()
    {
        ENGINE_LOG_INFO_TAG("Renderer", "OpenGLContext::Create");

        auto* Window = static_cast<GLFWwindow*>(m_WindowHandle);
        
        glfwMakeContextCurrent(Window);

        int GladInitializationResult = gladLoadGLLoader(reinterpret_cast<GLADloadproc>(glfwGetProcAddress));
        ENGINE_VERIFY(GladInitializationResult, "Failed to create OpenGL context!")

        ENGINE_LOG_INFO_TAG("Renderer", "Graphics Card Info:");
        ENGINE_LOG_INFO_TAG("Renderer", "  Device: {}", glGetString(GL_RENDERER));
        ENGINE_LOG_INFO_TAG("Renderer", "  Vendor: {}", glGetString(GL_VENDOR));
        ENGINE_LOG_INFO_TAG("Renderer", "  Driver Version: {}", glGetString(GL_VERSION));

        bool bIsOpenGL45Supported = GLVersion.major >= 4 && GLVersion.minor >= 5;
        ENGINE_VERIFY(bIsOpenGL45Supported, "Failed to create OpenGL context! The minimum supported version is OpenGL 4.5!");
    }

    void OpenGLContext::SwapBuffers()
    {
        glfwSwapBuffers(static_cast<GLFWwindow*>(m_WindowHandle));
    }
}
