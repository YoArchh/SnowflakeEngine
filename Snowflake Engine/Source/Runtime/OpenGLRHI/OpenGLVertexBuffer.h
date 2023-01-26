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

    private:
        uint32_t m_VertexBufferHandle;
    };
}
