#pragma once

class VertexBuffer {
private:
	unsigned int m_RenderedID;		//OpenGL ID Unique to opengl so that in future if some other apis are integrated
public:
	VertexBuffer(const void* data, unsigned int size);
	~VertexBuffer();

	void Bind() const;
	void UnBind() const;
};