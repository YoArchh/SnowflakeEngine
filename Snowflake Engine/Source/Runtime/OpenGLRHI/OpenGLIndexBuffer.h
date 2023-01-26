#pragma once

#include "Renderer/IndexBuffer.h"

namespace Snowflake
{
    class OpenGLIndexBuffer : public IndexBuffer
    {
    public:
        OpenGLIndexBuffer(void* BufferData, uint32_t BufferSize);
        virtual ~OpenGLIndexBuffer();

        virtual void Bind() const override;
        virtual void Unbind() const override;

        virtual uint32_t GetCount() const override { return m_Size / sizeof(uint32_t); }
        
    private:
        uint32_t m_IndexBufferHandle;
        uint32_t m_Size;
    };
}
