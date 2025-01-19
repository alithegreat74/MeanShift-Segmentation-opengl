#include <iostream>
#include "Application/Window.h"

int main()
{
	std::unique_ptr<MeanShift::Window> window = MeanShift::Window::CreateWindow();
	window->Update();
	return 0;
}