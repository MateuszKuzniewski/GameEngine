#include "VertexBuffer.h"
#include "GL/glew.h"

VertexBuffer::VertexBuffer(const void* vertices, uint32_t size)
{
    glGenBuffers(1, &m_RendererID);
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);
    glBufferData(GL_ARRAY_BUFFER, size, vertices, GL_STATIC_DRAW);
}
VertexBuffer::~VertexBuffer()
{
    glDeleteBuffers(1, &m_RendererID);
}

void VertexBuffer::Bind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, m_RendererID);

}
void VertexBuffer::Unbind() const
{
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void VertexBuffer::SetLayout(const BufferLayout& layout)
{
    m_Layout = layout;
}

const BufferLayout& VertexBuffer::GetLayout() const
{
    return m_Layout;
}


