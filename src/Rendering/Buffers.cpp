#include "Buffers.h"
#include <glad/glad.h>

namespace MeanShift {
	

	VertexBuffer::VertexBuffer(const void* verticies, size_t size)
	{
		glCreateBuffers(1, &m_RendererId);
		Bind();
		glBufferData(GL_ARRAY_BUFFER, size, verticies, GL_STATIC_DRAW);
	}
	VertexBuffer::~VertexBuffer()
	{
		glDeleteBuffers(1, &m_RendererId);
	}
	void VertexBuffer::Bind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, m_RendererId);
	}
	void VertexBuffer::Unbind()
	{
		glBindBuffer(GL_ARRAY_BUFFER, 0);
	}
	ArrayBuffer::ArrayBuffer()
	{
		glCreateVertexArrays(1, &m_RendererId);
		Bind();
		VertexBuffer vbo;
		glVertexAttribPointer(0, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)0);
		glEnableVertexAttribArray(0);
		glVertexAttribPointer(1, 2, GL_FLOAT, false, 4 * sizeof(float), (void*)(2 * sizeof(float)));
		glEnableVertexAttribArray(1);
		vbo.Unbind();
		Unbind();
	}
	ArrayBuffer::~ArrayBuffer()
	{
		glDeleteVertexArrays(1, &m_RendererId);
	}
	void ArrayBuffer::Bind()
	{
		glBindVertexArray(m_RendererId);
	}
	void ArrayBuffer::Unbind()
	{
		glBindVertexArray(0);
	}
}
