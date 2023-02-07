#include "SnowflakePCH.h"
#include "RendererAPI.h"

#include "Renderer/Renderer.h"

#include "OpenGLRHI/OpenGLRenderer.h"

namespace Snowflake
{
    Scope<RendererAPI> RendererAPI::Create()
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPIType::OpenGL: return CreateScope<OpenGLRenderer>();
            case RendererAPIType::Vulkan: ENGINE_VERIFY(false, "Failed to create renderer API instance! Vulkan isn't supported!") return nullptr;
            case RendererAPIType::Direct3D11: ENGINE_VERIFY(false, "Failed to create renderer API instance! Direct3D11 isn't supported!") return nullptr;
            case RendererAPIType::Direct3D12: ENGINE_VERIFY(false, "Failed to create renderer API instance! Direct3D12 isn't supported!") return nullptr;
            default: ENGINE_VERIFY(false, "Failed to create renderer API instance! Unknown/unsupported graphics API!") return nullptr;
        }
    }
}
