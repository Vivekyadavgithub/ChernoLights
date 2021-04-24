#include "ModelLoading.h"

void ModelLoading::Draw(Shader& shader)
{
}

void ModelLoading::loadModel(std::string path)
{
}

void ModelLoading::processNode(aiNode* node, const aiScene* scene)
{
}

Mesh ModelLoading::processMesh(aiMesh* mesh, const aiScene* scene)
{
	return Mesh();
}

std::vector<Textureinfo> ModelLoading::loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName)
{
	return std::vector<Textureinfo>();
}
