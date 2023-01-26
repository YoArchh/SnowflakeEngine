#include "SnowflakePCH.h"
#include "OpenGLVertexBuffer.h"

#include <glad/glad.h>

namespace Snowflake
{
    OpenGLVertexBuffer::OpenGLVertexBuffer(void* BufferData, uint32_t BufferSize, VertexBufferUsage BufferUsage)
    {
        glCreateBuffers(1, &m_VertexBufferHandle);
        glNamedBufferData(m_VertexBufferHandle, BufferSize, BufferData, BufferUsage);
    }

    OpenGLVertexBuffer::~OpenGLVertexBuffer()
    {
        glDeleteBuffers(1, &m_VertexBufferHandle);
    }

    void OpenGLVertexBuffer::Bind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_VertexBufferHandle);
    }

    void OpenGLVertexBuffer::Unbind() const
    {
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
}
