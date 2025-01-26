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
		//Load the two vertex and fragment shader from file
		m_MeanShiftProgram = std::make_unique<ShaderProgram>
			("Assets/Shaders/MeanShiftVertexShader.glsl", "Assets/Shaders/MeanShiftFragmentShader.glsl");
		//Load the two vertex and fragment shader from file
		m_NormalTextureDisplayProgram = std::make_unique<ShaderProgram>
			("Assets/Shaders/NormalTextureDisplayVertexShader.glsl", "Assets/Shaders/NormalTextureDisplayFragmentShader.glsl");

		//Create a basic vertex array to render a quad
		m_VertexArray = std::make_unique<VertexArray>();
		//Load the input texture from file
		m_InputTexture = std::make_unique<Texture>("Assets/Textures/1.jpg");

		//Allocate the two ping pong textures
		m_PingPongTextures = std::vector<std::unique_ptr<Texture>>(2);
		//Allocate the two ping pong framebuffers
		m_PingPongFrameBuffers = std::vector<std::unique_ptr<FrameBuffer>>(2);

		//Create two framebuffers and two texturs and attaching them to each other
		for (int i = 0; i < 2; i++) {
			m_PingPongFrameBuffers[i] = std::make_unique<FrameBuffer>();
			m_PingPongTextures[i] = std::make_unique<Texture>(m_InputTexture->GetWidth(), m_InputTexture->GetHeight(), m_InputTexture->GetChannelNumber());
			m_PingPongFrameBuffers[i]->AttachTexture(*m_PingPongTextures[i]);
		}
		
		//render the input texture on the first framebuffer to copy the input texture to the first pingpong texture
		m_PingPongFrameBuffers[0]->Bind();
		m_NormalTextureDisplayProgram->Bind();
		m_InputTexture->Bind();
		m_VertexArray->Bind();
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
			//Render the debug window
			{
				ImGui::Begin("Mean Shift Debug Window");
				ImGui::DragFloat("Kernel Radius", &m_MeanShiftValues.KernelRadius);
				ImGui::DragFloat("Color Weight", &m_MeanShiftValues.ColorWeight);
				ImGui::DragFloat("Spatial Weight", &m_MeanShiftValues.SpatialWeight);
				ImGui::DragInt("Max Iterations", &m_MeanShiftValues.MaxIterations);
				ImGui::End();
			}

			//Set Mean shift shader as the current running shader
			m_MeanShiftProgram->Bind();
			m_MeanShiftProgram->SetUniform("uTexelSize", 1.0f / 1280.0f, 1.0f / 720.0f);
			m_MeanShiftProgram->SetUniform("uRadius", m_MeanShiftValues.KernelRadius);
			m_MeanShiftProgram->SetUniform("uColorWeight", m_MeanShiftValues.ColorWeight);
			
			GLuint readBuffer = 0;
			GLuint writeBuffer = 1;
			//render the scene back and fourth and run the mean shift algorithm on the previous picture
			//this happens so our previous changes to the texture wouldn't be rest
			for (int i = 0; i < m_MeanShiftValues.MaxIterations; i++) { 
				m_PingPongFrameBuffers[writeBuffer]->Bind();
				m_PingPongTextures[readBuffer]->Bind();
				glDrawArrays(GL_TRIANGLES, 0, 6);
				std::swap(readBuffer, writeBuffer);
			}

			//Render the final texture on the screen
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