#pragma once

#include <string>
#include <unordered_map>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
private:
	std::string m_FilePath;
	std::string m_shaderName;
	unsigned int m_RendererID;
	// caching for uniforms
	std::unordered_map<std::string, int> m_UniformLocationCache;

public:
	Shader(const std::string& filepath, const std::string& shaderName);
	~Shader();

	void Bind() const;
	void Unbind() const;
	void SetUniform1i(const std::string& name, int value);
	void SetUniform1f(const std::string& name, float value);
	void SetUniform4f(const std::string& name, float v0, float v1, float v2, float v3);
	void SetUniformMat4(const std::string& name, glm::mat4 trans);
	void SetUniform3fv(const std::string& name, int count, glm::vec3 vec);
private:
	std::string ParseShader(std::string& shaderType);
	unsigned int CreateShader(const std::string& vertexShader, const std::string& fragmentShader);
	unsigned int CompileShader(unsigned int type, const std::string& source);
	unsigned int GetUniformLocation(const std::string& name);
};

