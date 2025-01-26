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

		for (int i = 0; i < 2; i++) {
			m_PingPongFrameBuffers[i] = std::make_unique<FrameBuffer>();
			m_PingPongTextures[i] = std::make_unique<Texture>(m_InputTexture->GetWidth(), m_InputTexture->GetHeight(), m_InputTexture->GetChannelNumber());
			m_PingPongFrameBuffers[i]->AttachTexture(*m_PingPongTextures[i]);
		}
		
		m_PingPongFrameBuffers[0]->Bind();
		m_NormalTextureDisplayProgram->Bind();
		m_InputTexture->Bind();
		m_ArrayBuffer->Bind();
		glDrawArrays(GL_TRIANGLES, 0, 6);
		
		ImGuiLayer::Initialize(m_Window);
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
			ImGuiLayer::BeginFrame();

			{
				ImGui::Begin("Mean Shift Debug Window");
				ImGui::DragFloat("Kernel Radius", &m_MeanShiftValues.KernelRadius);
				ImGui::DragFloat("Color Weight", &m_MeanShiftValues.ColorWeight);
				ImGui::End();
			}
			m_MeanShiftProgram->Bind();
			m_MeanShiftProgram->SetUniform("uTexelSize", 1.0f / 1280.0f, 1.0f / 720.0f);
			m_MeanShiftProgram->SetUniform("uRadius", m_MeanShiftValues.KernelRadius);
			m_MeanShiftProgram->SetUniform("uColorWeight", m_MeanShiftValues.ColorWeight);
			
			GLuint readBuffer = 0;
			GLuint writeBuffer = 1;
			for (int i = 0; i < 5; i++) { // Perform 5 iterations per frame
				m_PingPongFrameBuffers[writeBuffer]->Bind();
				m_PingPongTextures[readBuffer]->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 6);
				std::swap(readBuffer, writeBuffer);
			}
			FrameBuffer::Unbind();
			glClear(GL_COLOR_BUFFER_BIT);
			m_NormalTextureDisplayProgram->Bind();
			m_PingPongTextures[readBuffer]->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);

			ImGuiLayer::EndFrame();
			glfwSwapBuffers(m_Window);
			glfwPollEvents();
		}
	}
	std::unique_ptr<Window> Window::CreateWindow(const WindowInfo& info)
	{
		return std::make_unique<Window>(info);
	}
}