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
		glGenTextures(1, &m_RendererId);
		Bind();
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
		uint32_t textureChannel = textureInfo.nChannels == 1 ? GL_RED : textureInfo.nChannels == 3 ? GL_RGB : GL_RGBA;
		glTexImage2D(GL_TEXTURE_2D, 0, textureChannel, textureInfo.width, textureInfo.height, 0, textureChannel, GL_UNSIGNED_BYTE, textureInfo.data);
		glGenerateMipmap(GL_TEXTURE_2D);
		TextureLoader::UnloadTexture(textureInfo.data);
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