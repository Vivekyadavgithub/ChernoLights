#pragma once
#include <vector>
#include <string>
#include <memory>

#include "Renderer.h"
#include "VertexArray.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "IndexBuffer.h"

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

enum class DrawType{
	gl_Triangles,
	gl_Point,
	gl_Points
};
class SphereDrawing
{
private:
	std::vector<float> vertices;
	std::vector<float> normals;
	std::vector<float> texCoords;
	std::vector<unsigned int> indices;
	std::vector<unsigned int> lineIndices;
	const float PI = acos(-1);
	VertexArray va;

	//Shader* shader;
	int m_SectorCount, m_StackCount;
	float m_Radius;

	std::string shaderPath, shaderName;
private:
	void setUpCoordinates();
	void setVertexBuffer();
	void getIndices();
	void setIndexBuffer();
public:

	SphereDrawing(int sectorCount, int stackCount, float radius = 1.0f);
	void setShaderPath(const std::string& path, const std::string& name);
	void setUniforms(glm::mat4 model, glm::mat4 projection, glm::mat4 view);
	void draw();
	void setUpGui();
};

