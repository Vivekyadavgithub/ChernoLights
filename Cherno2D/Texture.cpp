#include "Texture.h"
#include <iostream>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"
Texture::Texture(const std::string& path)
	:
	m_RendererID(0),
	m_FilePath(path),
	m_LocalBuffer(nullptr),
	m_Width(0),
	m_Height(0),
	m_BPP(0)
{
	//stbi_set_flip_vertically_on_load(1);
	m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4);
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE );
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP);
	
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8, m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer);
	//glGenerateMipmap(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, 0);

	if (m_LocalBuffer)
		stbi_image_free(m_LocalBuffer);
}

Texture::Texture(std::vector<std::string> faces)
	:
	m_RendererID(0),
	m_FilePath(faces[0]),
	m_LocalBuffer(nullptr),
	m_Width(0),
	m_Height(0),
	m_BPP(0)
{
	//stbi_set_flip_vertically_on_load(1);
	glGenTextures(1, &m_RendererID);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);

	for (unsigned int i = 0; i < faces.size(); i++)
	{
		unsigned char* data = stbi_load(faces[i].c_str(), &m_Width, &m_Height, &m_BPP, 0);
		if (data)
		{
			glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, GL_RGB, m_Width, m_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
			stbi_image_free(data);
		}
		else
		{
			std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
			stbi_image_free(data);
		}
	}
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
}
Texture::~Texture()
{
	glDeleteTextures(1, &m_RendererID);
}

void Texture::Bind(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_2D, m_RendererID);
}

void Texture::BindCubeMap(unsigned int slot) const
{
	glActiveTexture(GL_TEXTURE0 + slot);
	glBindTexture(GL_TEXTURE_CUBE_MAP, m_RendererID);
}
void Texture::Unbind() const
{
	glBindTexture(GL_TEXTURE_2D, 0);
}
