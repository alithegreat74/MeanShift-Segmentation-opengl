#pragma once
#include <memory>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "Rendering/Buffers.h"
#include <iostream>
#include "Rendering/Shader.h"
#include "Rendering/Texture.h"
#include <vector>

namespace MeanShift
{
	struct WindowInfo {
		const char* WindowName;
		float Width, Height;
		WindowInfo(const char* windowName = "MeanShift Segmentation", float width = 1280.0f, float heigth = 720.0f)
			:WindowName(windowName), Width(width), Height(heigth)
		{}
	};
	//This struct is made only for debugging purposes 
	// (to get the right amount for our mean shift algorithm)
	struct MeanShiftValues {
		float TexelSize[2] = {
			1 / 1280.0f,1 / 720.0f
		};
		float KernelRadius = 5.0f;
		float ColorWeight = 50.0f;
	};

	class Window {
	public:
		Window(const WindowInfo& info);
		~Window();
		void Update();
		static std::unique_ptr<Window> CreateWindow(const WindowInfo& info = WindowInfo());
	private:
		GLFWwindow* m_Window = nullptr;
		std::unique_ptr<ArrayBuffer> m_ArrayBuffer;
		std::unique_ptr<ShaderProgram> m_MeanShiftProgram;
		std::unique_ptr<ShaderProgram> m_NormalTextureDisplayProgram;
		std::unique_ptr<Texture> m_InputTexture;
		std::vector<std::unique_ptr<Texture>>m_PingPongTextures;
		std::vector<std::unique_ptr<FrameBuffer>>m_PingPongFrameBuffers;
		MeanShiftValues m_MeanShiftValues;
	};

}