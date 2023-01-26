#include "SnowflakePCH.h"
#include "RendererContext.h"

#include "Renderer/Renderer.h"

#include "OpenGLRHI/OpenGLContext.h"

namespace Snowflake
{
    Scope<RendererContext> RendererContext::CreateContext(void* WindowHandle)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPIType::OpenGL: return CreateScope<OpenGLContext>(WindowHandle);
            case RendererAPIType::Vulkan: ENGINE_VERIFY(false, "Failed to create renderer context! Vulkan isn't supported!") return nullptr;
            case RendererAPIType::Direct3D11: ENGINE_VERIFY(false, "Failed to create renderer context! Direct3D11 isn't supported!") return nullptr;
            case RendererAPIType::Direct3D12: ENGINE_VERIFY(false, "Failed to create renderer context! Direct3D12 isn't supported!") return nullptr;
            default: ENGINE_VERIFY(false, "Failed to create renderer context! Unknown/unsupported graphics API!") return nullptr;
        }
    }
}
