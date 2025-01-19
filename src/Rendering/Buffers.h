#pragma once
#include <stdint.h>
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

	class ArrayBuffer
	{
	public:
		ArrayBuffer();
		~ArrayBuffer();
		void Bind();
		void Unbind();
	private:
		uint32_t m_RendererId;
	};

	class FrameBuffer
	{

	};
} 