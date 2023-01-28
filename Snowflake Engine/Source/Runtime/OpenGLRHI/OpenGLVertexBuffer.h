#pragma once

#include "Renderer/VertexBuffer.h"

namespace Snowflake
{
    class OpenGLVertexBuffer : public VertexBuffer
    {
    public:
        OpenGLVertexBuffer(void* BufferData, uint32_t BufferSize, VertexBufferUsage BufferUsage);
        virtual ~OpenGLVertexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual const BufferLayout& GetBufferLayout() const override { return m_BufferLayout; }
        virtual void SetBufferLayout(const BufferLayout& InBufferLayout) override { m_BufferLayout = InBufferLayout; }
        
    private:
        uint32_t m_VertexBufferHandle;
        BufferLayout m_BufferLayout;
    };
}
