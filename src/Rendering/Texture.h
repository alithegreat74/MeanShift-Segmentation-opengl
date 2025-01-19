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
		~Texture();
		void Bind();
		void Unbind();
	private:
		uint32_t m_RendererId;
	};
}