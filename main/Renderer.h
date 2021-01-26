#pragma once

#include <GL/glew.h>

#include"IndexBuffer.h"
#include"VertexArray.h"
#include"Shader.h"


#define ASSERT(x) if(!(x)) __debugbreak();
#define GLLogCall(x) ClearError();\
	x;\
	ASSERT(GetError(#x,__FILE__,__LINE__))

void ClearError();


bool GetError(const char* func, const char* file, unsigned int line);

class Renderer
{
public:
	void Clear() const;
	void Draw(const VertexArray & va, const IndexBuffer & ib, const Shader & shader) const;
};