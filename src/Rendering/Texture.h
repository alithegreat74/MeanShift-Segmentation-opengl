#pragma once
#include <stdint.h>
namespace MeanShift
{
	struct TextureInfo
	{
		int width, height, nChannels;
		unsigned char* data;
	};

	class TextureLoader {
	public:
		static TextureInfo LoadTexture(const char* filePath);
		static void UnloadTexture(unsigned char* data);
	};

	class Texture {
	public:
		Texture(const char* filePath);
		Texture(int width,int height,int nChannels);
		~Texture();
		void Bind();
		void Unbind();
		uint32_t GetId() const { return m_RendererId; }
		inline int GetWidth()const { return m_Width; }
		inline int GetHeight()const { return m_Height; }
		inline int GetChannelNumber()const { return m_ChannelNumber; }
	private:
		int m_Width, m_Height, m_ChannelNumber;
		uint32_t m_RendererId;
	};
}