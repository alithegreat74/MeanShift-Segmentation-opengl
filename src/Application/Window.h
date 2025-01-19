#pragma once
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Rendering/Buffers.h"
#include <iostream>
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"

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
	private:
		GLFWwindow* m_Window = nullptr;
		std::shared_ptr<ArrayBuffer> m_ArrayBuffer;
		std::shared_ptr<ShaderProgram> m_QuadProgram;
		std::shared_ptr<Texture> m_QuadTexture;
	};

}