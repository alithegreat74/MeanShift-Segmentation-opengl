#include "Window.h"
#include <iostream>

namespace MeanShift
{
	Window::Window(const WindowInfo& info) {
		std::cout << "Creating window" << std::endl;
	}

	Window::~Window()
	{
		std::cout << "Removing Window" << std::endl;
	}

	void Window::Update()
	{
		std::cout << "Update" << std::endl;
	}
	std::unique_ptr<Window> Window::CreateWindow(const WindowInfo& info)
	{
		return std::make_unique<Window>(info);
	}
}