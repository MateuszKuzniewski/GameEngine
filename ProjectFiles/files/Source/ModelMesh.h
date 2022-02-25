#pragma once
#include <string>
#include <vector>
#include <glm.hpp>

struct VectorComponents
{
	std::vector<float> x, y, z;
};

class ModelMesh
{
public:

	ModelMesh() = default;
	ModelMesh(const std::string& path);
	~ModelMesh();


	std::vector<uint32_t> GetIndecies();
	std::vector<float> GetVertices();
	glm::vec3 GetHighestVert() const;
	glm::vec3 GetLowestVert() const;
	void GenerateQuadData();

private:

	void CombineVertData(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<uint32_t>& vertIndices, std::vector<uint32_t>& normalIndices);
	glm::vec3 CheckForHighestValue(const std::vector<glm::vec3>& vector);
	glm::vec3 CheckForLowestValue(const std::vector<glm::vec3>& vector);
	VectorComponents GetVectorComponents(const std::vector <glm::vec3>& vector);

private:

	glm::vec3 m_HighestVerticesValue, m_LowestVerticesValue;

	std::vector<uint32_t> m_VertexIndices, m_TextureIndices, m_NormalIndices;
	std::vector<glm::vec3> m_Vertices, m_Normals;
	std::vector<glm::vec2> m_TextureCoordinates;

	std::vector<float> m_VertData; 
	std::vector<uint32_t> m_IndicesData; 


};

