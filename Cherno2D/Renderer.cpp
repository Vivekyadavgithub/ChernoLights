#include "Renderer.h"
#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);
}

bool GLLogCall(const char* function, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "[Opengl Error] (" << error << "): "
			<< function << " " << file << ":" << line << "\n";
		return false;
	}
	return true;
}

void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();
	va.Bind();
	ib.Bind();
	//glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
	glDrawArrays(GL_TRIANGLES, 0, 36);
	//glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr);
	shader.Unbind();
	va.Unbind();
	ib.Unbind();
}

void Renderer::Clear() const
{
	glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
	glEnable(GL_DEPTH_TEST);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
