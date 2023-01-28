#pragma once

#include "Renderer/RendererAPI.h"

namespace Snowflake
{
    class OpenGLRendererAPI : public RendererAPI
    {
    public:
        virtual void Initialize() override;
        
        virtual void Clear(BufferMask InBufferMask) override;
        
        virtual void ClearColor(float Red, float Green, float Blue, float Alpha) override;

        virtual void DrawIndexed(uint32_t Count, PrimitiveType DrawType, bool bDepthTest = true) override;
    };
}
