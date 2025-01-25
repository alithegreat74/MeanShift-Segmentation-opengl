#pragma once

#include <stdint.h>
#include <string_view>

namespace MeanShift {
	class Shader {
	public:
		Shader(const char* filePath, uint32_t shaderType);
		~Shader();
		operator uint32_t() const { return m_RendererId; }
		inline uint32_t GetShaderType()const { return m_ShaderType; }
	private:
		std::string ReadFromPath(const char* filePath);
		void ValidateShader()const;
	private:
		uint32_t m_RendererId;
		uint32_t m_ShaderType;
	};

	class ShaderProgram {
	public:
		ShaderProgram(const char* vertexShaderPath, const char* fragmentShader);
		~ShaderProgram();

		void SetUniform(const char* uniformName, int value);
		void SetUniform(const char* uniformName, float value);
		void SetUniform(const char* uniformName, float value1, float value2);

		void Bind();
		void Unbind();
	private:
		void InitializeProgram(const Shader& vertexShader,const Shader& fragmentShder);
		void ValidateProgram();
	private:
		uint32_t m_RendererId;
	};
}