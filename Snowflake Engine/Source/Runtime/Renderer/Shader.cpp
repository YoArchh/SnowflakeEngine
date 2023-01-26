#include "SnowflakePCH.h"
#include "Shader.h"

#include "Renderer/Renderer.h"

#include "OpenGLRHI/OpenGLShader.h"

namespace Snowflake
{
    Ref<Shader> Shader::CreateShader(const std::filesystem::path& Filepath)
    {
        switch (Renderer::GetCurrentAPI())
        {
            case RendererAPIType::OpenGL: return CreateRef<OpenGLShader>(Filepath);
            case RendererAPIType::Vulkan: ENGINE_VERIFY(false, "Failed to create shader! Vulkan isn't supported!") return nullptr;
            case RendererAPIType::Direct3D11: ENGINE_VERIFY(false, "Failed to create shader! Direct3D11 isn't supported!") return nullptr;
            case RendererAPIType::Direct3D12: ENGINE_VERIFY(false, "Failed to create shader! Direct3D12 isn't supported!") return nullptr;
            default: ENGINE_VERIFY(false, "Failed to create shader! Unknown/unsupported graphics API") return nullptr;
        }
    }
}
