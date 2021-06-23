#include "Shader.h"
 
#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include "Renderer.h"

Shader::Shader(const std::string& filepath, const std::string& shaderName)
	: 
	m_FilePath(filepath),
	m_shaderName(shaderName),
	m_RendererID(0)
{
	m_FilePath += '/';
	ShaderProgramSource source;
	std::string vertPath = m_FilePath + m_shaderName + "vertex.glsl";
	std::string fragPath = m_FilePath + m_shaderName + "fragment.glsl";
	source.VertexSource = ParseShader(vertPath);
	source.FragmentSource = ParseShader(fragPath);
	m_RendererID = CreateShader(source.VertexSource, source.FragmentSource);
}

Shader::~Shader()
{
	glDeleteProgram(m_RendererID);
}

void Shader::Bind() const
{
	glUseProgram(m_RendererID);
}

void Shader::Unbind() const
{
	glUseProgram(0);
}

void Shader::SetUniform1i(const std::string& name, int value)
{
	glUniform1i(GetUniformLocation(name), value);
}

void Shader::SetUniform1f(const std::string& name, float value)
{
	glUniform1f(GetUniformLocation(name), value);
}

std::string Shader::ParseShader(std::string& shader)
{
	std::ifstream stream(shader);
	std::string line;
	std::stringstream ss;
	while (getline(stream, line))
	{
			ss << line << "\n";
	}	
	return  ss.str();

}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		if(type == GL_VERTEX_SHADER)
			std::cout << "Failed to compile " << "vertex " << " shader!" << std::endl;
		else if(type == GL_FRAGMENT_SHADER)
			std::cout << "Failed to compile " << "fragment " << " shader!" << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
	return false;
}

unsigned int Shader::CreateShader(const std::string& vertexShader, const std::string& fragmentShader)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShader);
	
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShader);
	glAttachShader(program, vs);
	glAttachShader(program, fs);

	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

void Shader::SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3)
{
	glUniform4f(GetUniformLocation(name), v0, v1, v2, v3);
}

void Shader::SetUniformMat4(const std::string& name, glm::mat4 trans)
{
	glUniformMatrix4fv(GetUniformLocation(name), 1, GL_FALSE, glm::value_ptr(trans));
}

void Shader::SetUniform3fv(const std::string& name, int count, glm::vec3 vec)
{
	glUniform3fv(GetUniformLocation(name), count, glm::value_ptr(vec));
}

unsigned int Shader::GetUniformLocation(const std::string& name)
{
	if (m_UniformLocationCache.find(name) != m_UniformLocationCache.end())
	{
		return m_UniformLocationCache[name];
	}
	int location = glGetUniformLocation(m_RendererID, name.c_str());
	if (location == -1)
		std::cout << "Warning: uniform '" << name << "' doesn't exist!" << std::endl;
	m_UniformLocationCache[name] = location;
	return m_UniformLocationCache[name];
}
