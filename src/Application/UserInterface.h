#pragma once
#include <GLFW/glfw3.h>
#include <imgui.h>
#include <backends/imgui_impl_glfw.h>
#include <backends/imgui_impl_opengl3.h>

namespace MeanShift {
	namespace ImGuiLayer {
		void Initialize(GLFWwindow* window);
		void BeginFrame();
		void EndFrame();
		void Cleanup();
	}
}