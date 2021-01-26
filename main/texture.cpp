#include "texture.h"

#include "vendor/stb_image/stb_image.h"

Texture::Texture(const std::string &Path)
	:m_Renderer_ID(0), m_filepath(Path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{
	stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(Path.c_str(), &m_Width, &m_Height, &m_BPP, 4);


	GLLogCall(glGenTextures(1, &m_Renderer_ID));
	GLLogCall(glBindTexture(GL_TEXTURE_2D, m_Renderer_ID));

	GLLogCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
	GLLogCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
	GLLogCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
	GLLogCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));

	GLLogCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
	GLLogCall(glBindTexture(GL_TEXTURE_2D, 0));

	if (m_LocalBuffer)
	{
		stbi_image_free(m_LocalBuffer);
	}





	

}

Texture::~Texture()
{

	GLLogCall(glDeleteTextures(1, &m_Renderer_ID));

}

void Texture::Bind(unsigned int slot) const
{
	GLLogCall(glActiveTexture(GL_TEXTURE0 + slot));
	GLLogCall(glBindTexture(GL_TEXTURE_2D, m_Renderer_ID));
}

void Texture::Unbind() const
{
	GLLogCall(glBindTexture(GL_TEXTURE_2D, 0));
}
