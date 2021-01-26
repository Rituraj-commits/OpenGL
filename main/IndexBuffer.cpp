#include"IndexBuffer.h"
#include"Renderer.h"

IndexBuffer::IndexBuffer(const unsigned int* data, unsigned int count):m_Count(count)
{
	ASSERT(sizeof(unsigned int) == sizeof(GLuint));

	
	GLLogCall(glGenBuffers(1, &m_RendererID));
	GLLogCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,m_RendererID));
	GLLogCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

IndexBuffer::~IndexBuffer()
{
	GLLogCall(glDeleteBuffers(1, &m_RendererID));
}

void IndexBuffer::Bind() const
{
	GLLogCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_RendererID)); // Bind a named Buffer object
}

void IndexBuffer::Unbind() const 
{
	GLLogCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0)); // Bind a named Buffer object

}