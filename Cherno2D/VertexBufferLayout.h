#pragma once
#include <vector>
#include <glad/glad.h>

struct VertexBufferElement
{
	unsigned int type;
    int count;
	uint8_t normalized;

	static unsigned int GetSizeofType(unsigned int type)
	{
		switch (type)
		{
		case GL_FLOAT: return sizeof(GL_FLOAT);
		case GL_UNSIGNED_INT: return sizeof(GL_UNSIGNED_INT);
		case GL_UNSIGNED_BYTE: return sizeof(GL_UNSIGNED_BYTE);
		}
		return 0;
	}
};
class VertexBufferLayout
{
private:
	std::vector<VertexBufferElement> m_Elements;
	unsigned int m_Stride;
public:
	//VertexBufferLayout();

	template<typename T>
	void Push(int count)
	{
		//static_assert(false);
	}

	template<>
	void Push<float>(int count)
	{
		m_Elements.push_back({GL_FLOAT ,count, GL_FALSE});
		m_Stride += count * sizeof(GLfloat);
	}

	template<>
	void Push<unsigned int>(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_INT ,count, GL_FALSE });
		m_Stride += count * sizeof(GLuint);
	}

	template<>
	void Push<unsigned char>(int count)
	{
		m_Elements.push_back({ GL_UNSIGNED_BYTE ,count, GL_TRUE });
		m_Stride += count * sizeof(GLbyte);
	}

	inline const std::vector<VertexBufferElement> GetElements() const { return m_Elements;  }
	inline unsigned int GetStride() const { return m_Stride; }
};

