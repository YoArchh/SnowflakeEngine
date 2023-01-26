#pragma once

#include "Renderer/RendererContext.h"

namespace Snowflake
{
    class OpenGLContext : public RendererContext
    {
    public:
        OpenGLContext(void* WindowHandle);
        
        void Initialize() override;
        void SwapBuffers() override;

    private:
        void* m_WindowHandle;
    };
}