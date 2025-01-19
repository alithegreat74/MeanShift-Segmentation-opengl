#include "Shader.h"

#include <glad/glad.h>
#include <fstream>
#include <cassert>
#include <string>
#include <sstream>
#include <iostream>

namespace MeanShift{
	Shader::Shader(const char* filePath, uint32_t shaderType):
		m_RendererId(-1),m_ShaderType(shaderType)
	{
		m_RendererId = glCreateShader(m_ShaderType);
		std::string source = ReadFromPath(filePath);
		const char* csource = source.c_str(); //Need to cast the source to c style string because glad only takes c style strings
		glShaderSource(m_RendererId, 1, &csource, NULL);
		glCompileShader(m_RendererId);
		ValidateShader();
	}
	Shader::~Shader()
	{
		glDeleteShader(m_RendererId);
	}
	std::string Shader::ReadFromPath(const char* filePath)
	{
		std::ifstream file(filePath);
		assert(file.is_open() && "Unable to open the file");
		std::stringstream buffer;
		buffer << file.rdbuf();
		return buffer.str();
	}
	void Shader::ValidateShader() const
	{
		int success;
		glGetShaderiv(m_RendererId, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			char log[512];
			glGetShaderInfoLog(m_RendererId, 512, NULL, log);
			std::cout << log;
		}
	}
	//TODO: Add Support for computte shaders
	ShaderProgram::ShaderProgram(const char* vertexShaderPath, const char* fragmentShaderPath)
		:m_RendererId(-1)
	{
		Shader vertexShader(vertexShaderPath, GL_VERTEX_SHADER);
		Shader fragmentShader(fragmentShaderPath, GL_FRAGMENT_SHADER);
		InitializeProgram(vertexShader, fragmentShader);
	}
	ShaderProgram::~ShaderProgram()
	{
		glDeleteProgram(m_RendererId);
	}
	void ShaderProgram::InitializeProgram(const Shader& vertexShader, const Shader& fragmentShder)
	{
		m_RendererId = glCreateProgram();
		glAttachShader(m_RendererId, vertexShader.GetId());
		glAttachShader(m_RendererId, fragmentShder.GetId());
		glLinkProgram(m_RendererId);
		ValidateProgram();
	}
	void ShaderProgram::Bind()
	{
		glUseProgram(m_RendererId);
	}
	void ShaderProgram::Unbind()
	{
		glUseProgram(0);
	}
	void ShaderProgram::ValidateProgram()
	{
		int success;
		glGetProgramiv(m_RendererId, GL_LINK_STATUS, &success);
		if (success)
		{
			char log[512];
			glGetProgramInfoLog(m_RendererId, 512, NULL, log);
			std::cout << log;
		}
	}
}
