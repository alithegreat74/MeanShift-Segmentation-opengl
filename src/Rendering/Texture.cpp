#include "Texture.h"
#include <stb_image.h>
#include <cassert>
#include <glad/glad.h>

namespace MeanShift {
	TextureInfo TextureLoader::LoadTexture(const char* filePath) 
	{
		int width, height, nChannels;
		stbi_set_flip_vertically_on_load(true);
		unsigned char* data = stbi_load(filePath, &width, &height, &nChannels, 0);
		assert(data && "No textures found");
		return{ width,height,nChannels,data };
	}
	void TextureLoader::UnloadTexture(unsigned char* data)
	{
		stbi_image_free(data);
	}
	Texture::Texture(const char* filePath)
	{
		TextureInfo textureInfo = TextureLoader::LoadTexture(filePath);
		m_Width = textureInfo.width;
		m_Height = textureInfo.height;
		m_ChannelNumber = textureInfo.nChannels;
		glGenTextures(1, &m_RendererId);
		Bind();
		int32_t format = textureInfo.nChannels == 1 ? GL_RED :
			textureInfo.nChannels == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, format, textureInfo.width, textureInfo.height, 0, format, GL_UNSIGNED_BYTE, textureInfo.data);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		TextureLoader::UnloadTexture(textureInfo.data);
		Unbind();
	}
	// In Texture.cpp
	Texture::Texture(int width, int height, int nChannels)
		: m_Width(width), m_Height(height),
		m_ChannelNumber(nChannels)
	{
		glGenTextures(1, &m_RendererId);
		Bind();

		GLenum format = m_ChannelNumber == 1 ? GL_RED :
			m_ChannelNumber == 3 ? GL_RGB : GL_RGBA;

		// Create empty texture with proper dimensions
		glTexImage2D(GL_TEXTURE_2D, 0, format, m_Width, m_Height, 0,
			format, GL_UNSIGNED_BYTE, nullptr);

		Unbind();
	}
	Texture::~Texture()
	{
		glDeleteTextures(1, &m_RendererId);
	}
	void Texture::Bind()
	{
		glBindTexture(GL_TEXTURE_2D, m_RendererId);
	}
	void Texture::Unbind()
	{
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}