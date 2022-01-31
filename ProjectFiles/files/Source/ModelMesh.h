#pragma once
#include <string>
#include <vector>
#include <glm.hpp>

class ModelMesh
{
public:

	ModelMesh(const std::string& path);
	~ModelMesh();


	std::vector<uint32_t> GetIndecies();
	std::vector<float> GetVertices();
	

private:

	void CombineVertData();

private:

	uint32_t m_RendererID;
	std::vector<uint32_t> m_VertexIndices, m_TextureIndices, m_NormalIndices;
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec3> m_Normals;
	std::vector<glm::vec2> m_TextureCoordinates;

	std::vector<float>m_VertData; 
	std::vector<uint32_t>m_IndicesData; 

};

