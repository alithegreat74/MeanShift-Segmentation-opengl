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
			glClearColor(0.2, 0.2, 0.2, 1.0);
			glClear(GL_COLOR_BUFFER_BIT);
			glfwPollEvents();
			glfwSwapBuffers(m_Window);
		}
	}
	std::unique_ptr<Window> Window::CreateWindow(const WindowInfo& info)
	{
		return std::make_unique<Window>(info);
	}
}