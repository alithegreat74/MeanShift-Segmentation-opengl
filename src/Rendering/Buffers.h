#pragma once
#include <stdint.h>
#include "Texture.h"

namespace MeanShift {

	constexpr float QUAD_VERTICIES[] = {
		-1.0f,-1.0f,0.0f,0.0f,
		-1.0f, 1.0f,0.0f,1.0f,
		 1.0f,-1.0f,1.0f,0.0f,
		 1.0f,-1.0f,1.0f,0.0f,
		-1.0f, 1.0f,0.0f,1.0f,
		 1.0f, 1.0f,1.0f,1.0f,
	};
	class VertexBuffer {
	public:
		VertexBuffer(const void* verticies = QUAD_VERTICIES, size_t size = sizeof(QUAD_VERTICIES));
		~VertexBuffer();
		void Bind();
		void Unbind();

	private:
		 uint32_t m_RendererId;
	};

	class VertexArray
	{
	public:
		VertexArray();
		~VertexArray();
		void Bind();
		void Unbind();
	private:
		uint32_t m_RendererId;
	};

	class FrameBuffer
	{
	public:
		FrameBuffer();
		~FrameBuffer();

		void AttachTexture(const Texture& texture)const;
		void Bind()const;
		static void Unbind();
	private:
		uint32_t m_RendererId;
	};
} 