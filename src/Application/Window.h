#pragma once
#include <memory>
namespace MeanShift
{
	struct WindowInfo {
		const char* WindowName;
		float Width, Height;
		WindowInfo(const char* windowName = "MeanShift Segmentation", float width = 1280.0f, float heigth = 720.0f)
			:WindowName(windowName), Width(width), Height(heigth)
		{}
	};
	class Window {
	public:
		Window(const WindowInfo& info);
		~Window();
		void Update();
		static std::unique_ptr<Window> CreateWindow(const WindowInfo& info = WindowInfo());

	};
}