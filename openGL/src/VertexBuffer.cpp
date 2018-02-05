#include "VertexBuffer.h";
#include <gl/glew.h>

VertexBuffer::VertexBuffer(const void* data, unsigned int size) 
{
	glGenBuffers(1, &m_RenderedID);//declaring that above created buffer will be used in GPU for openGL
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderedID);//defining the buffer as array one... it is called binding
	glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW); //info about the data inside the buffer 
}

VertexBuffer::~VertexBuffer()
{
	glDeleteBuffers(1, &m_RenderedID);
}

void VertexBuffer::Bind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, m_RenderedID);
}

void VertexBuffer::UnBind() const
{
	glBindBuffer(GL_ARRAY_BUFFER, 0);
}