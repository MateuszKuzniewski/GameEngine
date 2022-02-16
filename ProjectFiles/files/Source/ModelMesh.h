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
	glm::vec3 GetHighestVert() const;
	glm::vec3 GetLowestVert() const;
	

private:

	void CombineVertData();
	glm::vec3 CheckForHighestValue(glm::vec3 values);
	glm::vec3 CheckForLowestValue(glm::vec3 values);

private:

	uint32_t m_RendererID;
	glm::vec3 m_HighestVerticesValue, m_LowestVerticesValue, m_Temp;
	glm::vec3 m_TempLowest = { 100.0f, 100.0f, 100.0f };
	std::vector<uint32_t> m_VertexIndices, m_TextureIndices, m_NormalIndices;
	std::vector<glm::vec3> m_Vertices;
	std::vector<glm::vec3> m_Normals;
	std::vector<glm::vec2> m_TextureCoordinates;

	std::vector<float>m_VertData; 
	std::vector<uint32_t>m_IndicesData; 

};

