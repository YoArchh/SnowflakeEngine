#include "SnowflakePCH.h"
#include "OpenGLRenderer.h"

#include <glad/glad.h>

namespace Snowflake
{
    static void DebugMessageCallback(GLenum Source, GLenum Type, GLuint ID, GLenum MessageSeverity, GLsizei Length, const GLchar* Message, const void* UserParams)
    {
        switch (MessageSeverity)
        {
            case GL_DEBUG_SEVERITY_LOW:
            {
                ENGINE_LOG_INFO_TAG("OpenGL Debug LOW", "{0}", Message);
                break;
            }
            case GL_DEBUG_SEVERITY_MEDIUM:
            {
                ENGINE_LOG_WARN_TAG("OpenGL Debug MEDIUM", "{0}", Message);
                break;
            }
            case GL_DEBUG_SEVERITY_HIGH:
            {
                ENGINE_LOG_ERROR_TAG("OpenGL Debug HIGH", "{0}", Message);
                ENGINE_ASSERT(false, "An OpenGL error has occurred!")
                break;
            }
            default: break;
        }
    }
    
    void OpenGLRenderer::Initialize()
    {
        #ifdef SNOWFLAKE_BUILD_DEBUG
            glDebugMessageCallback(DebugMessageCallback, nullptr);
            glEnable(GL_DEBUG_OUTPUT);
            glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
        #endif

        glEnable(GL_DEPTH_TEST);
    }

    void OpenGLRenderer::Clear(BufferMask InBufferMask)
    {
        switch (InBufferMask)
        {
            case BufferMask::Color:
            {
                glClear(GL_COLOR_BUFFER_BIT);
                break;
            }
            case BufferMask::Depth:
            {
                glClear(GL_DEPTH_BUFFER_BIT);
                break;
            }
            case BufferMask::Stencil:
            {
                glClear(GL_STENCIL_BUFFER_BIT);
                break;
            }
            case BufferMask::ColorAndDepth:
            {
                glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
                break;
            }
        }
    }

    void OpenGLRenderer::ClearColor(float Red, float Green, float Blue, float Alpha)
    {
        glClearColor(Red, Green, Blue, Alpha);
    }

    void OpenGLRenderer::DrawIndexed(uint32_t Count, PrimitiveType DrawType, bool bDepthTest)
    {
        GLenum GLPrimitiveType = 0;
        
        if (!bDepthTest)
            glDisable(GL_DEPTH_TEST);
        
        switch (DrawType)
        {
            case PrimitiveType::Triangles: GLPrimitiveType = GL_TRIANGLES; break;
            case PrimitiveType::Lines: GLPrimitiveType = GL_LINES; break;
        }

        glDrawElements(GLPrimitiveType, Count, GL_UNSIGNED_INT, nullptr);

        if (!bDepthTest)
            glEnable(GL_DEPTH_TEST);
    }
}
