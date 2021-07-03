#pragma once
#include <vector>

#include "Renderer.h"
class Texture
{
private:
	unsigned int m_RendererID;
	std::string m_FilePath;
	unsigned char* m_LocalBuffer;
	int m_Width, m_Height, m_BPP;

public:
	Texture(const std::string& path);
	Texture(std::vector<std::string> faces);
	~Texture();

	unsigned int TextureFromFile(const char* path, const std::string& directory, bool gamma = false);
	void Bind(unsigned int slot = 0) const;
	void BindCubeMap(unsigned int slot = 0) const;
	void Unbind() const;

	inline int GetWidth() const { return m_Width;  }
	inline int GetHeight() const { return m_Height; } 
	inline unsigned int GetId() const { return m_RendererID; }

};

