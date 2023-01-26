#include "SnowflakePCH.h"
#include "OpenGLIndexBuffer.h"

#include <glad/glad.h>

namespace Snowflake
{
    OpenGLIndexBuffer::OpenGLIndexBuffer(void* BufferData, uint32_t BufferSize)
        : m_Size(BufferSize)
    {
        glCreateBuffers(1, &m_IndexBufferHandle);
        glNamedBufferData(m_IndexBufferHandle, BufferSize, BufferData, GL_STATIC_DRAW);
    }

    OpenGLIndexBuffer::~OpenGLIndexBuffer()
    {
        glDeleteBuffers(1, &m_IndexBufferHandle);
    }

    void OpenGLIndexBuffer::Bind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IndexBufferHandle);
    }

    void OpenGLIndexBuffer::Unbind() const
    {
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    }
}
