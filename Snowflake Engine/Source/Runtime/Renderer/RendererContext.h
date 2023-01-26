#pragma once

namespace Snowflake
{
    class RendererContext
    {
    public:
        virtual ~RendererContext() = default;

        virtual void Initialize() = 0;
        virtual void SwapBuffers() = 0;

        static Scope<RendererContext> CreateContext(void* WindowHandle);
    };
}
