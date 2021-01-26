#include<iostream>
#include"Renderer.h"
#include"VertexArray.h"
#include"IndexBuffer.h"
#include"Shader.h"


void ClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GetError(const char* func, const char* file, unsigned int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[OpenGl] ( " << error << " )" << func << " " << file << " : " << line << std::endl;
		return false;
	}
	return true;
}

void Renderer::Clear() const
{
	GLLogCall(glClear(GL_COLOR_BUFFER_BIT));
}

void Renderer::Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const
{
	
	

	/*No need to bind vertex buffer as it is already bound within the vao*/

	shader.Bind();
	va.Bind();
	ib.Bind();
	
	GLLogCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));
}
