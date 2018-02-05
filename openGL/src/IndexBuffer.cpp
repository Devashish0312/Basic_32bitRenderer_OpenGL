#include "IndexBuffer.h";
#include <gl/glew.h>

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count)
	:m_Count(count)
{
	glGenBuffers(1, &m_RenderedID);//declaring that above created buffer will be used in GPU for openGL
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID);//defining the buffer as array one... it is called binding
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW); //info about the data inside the buffer 
}

IndexBuffer::~IndexBuffer()
{
	glDeleteBuffers(1, &m_RenderedID);
}

void IndexBuffer::Bind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RenderedID);
}

void IndexBuffer::UnBind() const
{
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}