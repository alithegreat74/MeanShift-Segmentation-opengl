#include "Window.h"
#include <iostream>
#include <cassert>


namespace MeanShift
{
	Window::Window(const WindowInfo& info) {
		assert(glfwInit() && "Unable to initialize glfw");
		m_Window = glfwCreateWindow(info.Width, info.Height, info.WindowName, NULL, NULL);
		assert(m_Window && "Unable to create a window");
		glfwMakeContextCurrent(m_Window);
		assert(gladLoadGL() && "Unable to load glad functions");
		m_QuadProgram = std::make_shared<ShaderProgram>("Assets/Shaders/QuadVertexShader.glsl", "Assets/Shaders/QuadFragmentShader.glsl");
		m_ArrayBuffer = std::make_shared<ArrayBuffer>();
		m_QuadTexture = std::make_shared<Texture>("Assets/Textures/1.jpg");
	}

	Window::~Window()
	{
		glfwDestroyWindow(m_Window);
		glfwTerminate();
	}

	void Window::Update()
	{
		while (!glfwWindowShouldClose(m_Window))
		{
			glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
			glClear(GL_COLOR_BUFFER_BIT);
			
			m_QuadProgram->Bind();
			m_ArrayBuffer->Bind();
			m_QuadTexture->Bind();
			glDrawArrays(GL_TRIANGLES, 0, 6);
			m_QuadTexture->Unbind();
			m_ArrayBuffer->Unbind();
			m_QuadProgram->Unbind();

			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
	}
	std::unique_ptr<Window> Window::CreateWindow(const WindowInfo& info)
	{
		return std::make_unique<Window>(info);
	}
}