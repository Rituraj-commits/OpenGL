#include"VertexBuffer.h"
#include"Renderer.h"

VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	
	GLLogCall( glGenBuffers(1, &m_RendererID));  // Generate Buffer object names
	GLLogCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind a named Buffer object
	GLLogCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW)); /* Creates and initializes a
																					buffer object's data store */
}

VertexBuffer::~VertexBuffer()
{
	GLLogCall(glDeleteBuffers(1, &m_RendererID));
}

void VertexBuffer::Bind() const 
{
	GLLogCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // Bind a named Buffer object
}

void VertexBuffer::Unbind() const
{
	GLLogCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // Bind a named Buffer object

}