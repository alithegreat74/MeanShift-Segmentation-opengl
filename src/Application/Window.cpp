#include "Window.h"
#include <iostream>
#include <cassert>
#include "UserInterface.h"
#include <imgui.h>

namespace MeanShift
{
	Window::Window(const WindowInfo& info) {
		assert(glfwInit() && "Unable to initialize glfw");
		m_Window = glfwCreateWindow(info.Width, info.Height, info.WindowName, NULL, NULL);
		assert(m_Window && "Unable to create a window");
		glfwMakeContextCurrent(m_Window);
		assert(gladLoadGL() && "Unable to load glad functions");
		m_MeanShiftProgram = std::make_unique<ShaderProgram>
			("Assets/Shaders/MeanShiftVertexShader.glsl", "Assets/Shaders/MeanShiftFragmentShader.glsl");
		m_NormalTextureDisplayProgram = std::make_unique<ShaderProgram>
			("Assets/Shaders/NormalTextureDisplayVertexShader.glsl", "Assets/Shaders/NormalTextureDisplayFragmentShader.glsl");

		m_ArrayBuffer = std::make_unique<ArrayBuffer>();
		m_InputTexture = std::make_unique<Texture>("Assets/Textures/1.jpg");
		m_PingPongTextures = std::vector<std::unique_ptr<Texture>>(2);
		m_PingPongFrameBuffers = std::vector<std::unique_ptr<FrameBuffer>>(2);
		
		for (size_t i = 0; i < 2; i++) {
			m_PingPongFrameBuffers[i] = std::make_unique<FrameBuffer>();
			m_PingPongTextures[i] = std::make_unique<Texture>(m_InputTexture->GetWidth(),m_InputTexture->GetHeight(),m_InputTexture->GetChannelNumber());
			m_PingPongFrameBuffers[i]->AttachTexture(*m_PingPongTextures[i]);
		}
		ImGuiLayer::Initialize(m_Window);

		m_PingPongFrameBuffers[0]->Bind();
		m_NormalTextureDisplayProgram->Bind();
		m_ArrayBuffer->Bind();
		m_InputTexture->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
	}

	Window::~Window()
	{
		ImGuiLayer::Cleanup();
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Update()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			m_MeanShiftProgram->Bind();
			m_MeanShiftProgram->SetUniform("uTexelSize", 1.0f / m_InputTexture->GetWidth(), 1.0f / m_InputTexture->GetHeight());
			m_MeanShiftProgram->SetUniform("uRadius", 7.0f);
			m_MeanShiftProgram->SetUniform("uColorWeight", 50.0f);
			uint32_t readBuffer = 0;
			uint32_t writeBuffer = 1;
			for (size_t i = 0; i < 5; i++) {
				m_PingPongFrameBuffers[writeBuffer]->Bind();
				m_PingPongTextures[readBuffer]->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 6);
				std::swap(readBuffer, writeBuffer);
			}

			m_PingPongFrameBuffers[0]->Unbind();
			glClear(GL_COLOR_BUFFER_BIT);
			m_NormalTextureDisplayProgram->Bind();
			m_PingPongTextures[readBuffer]->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);

			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}
	std::unique_ptr<Window> Window::CreateWindow(const WindowInfo& info)
	{
		return std::make_unique<Window>(info);
	}
}