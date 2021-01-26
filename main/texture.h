#pragma once

#include "Renderer.h"
#include<string>

class Texture
{
private:
	unsigned int m_Renderer_ID;
	std::string m_filepath;
	unsigned char *m_LocalBuffer;
	int m_Width, m_Height, m_BPP;
public:
	Texture(const std::string &Path);
	~Texture();
	
	void Bind(unsigned int slot=0) const;
	void Unbind() const;

	int GetWidth() const { return m_Width; }
	int GetHeight() const { return m_Height; }



};