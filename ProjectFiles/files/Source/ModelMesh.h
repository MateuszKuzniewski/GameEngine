#pragma once
#include <string>
#include <vector>
#include <glm.hpp>
#include "stb_image.h"

struct VectorComponents
{
	std::vector<float> x, y, z;
};

class ModelMesh
{
public:

	ModelMesh();
	~ModelMesh();


	void GenerateQuadData();
	void ParseOBJ(const std::string& path);
	void ParseHeightMap(const std::string& path);
	std::vector<uint32_t> GetIndices() const;
	std::vector<float> GetVertices() const;
	std::vector<float> GetRawVertices();
	std::vector<float> GetRawNormals();
	std::vector<uint32_t> GetRawIndices() const;
	glm::vec3 GetHighestVert() const;
	glm::vec3 GetLowestVert() const;
private:

	void Clear();
	void CombineVertData(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<uint32_t>& vertIndices, std::vector<uint32_t>& normalIndices);
	glm::vec3 CheckForHighestValue(const std::vector<glm::vec3>& vector);
	glm::vec3 CheckForLowestValue(const std::vector<glm::vec3>& vector);
	VectorComponents GetVectorComponents(const std::vector <glm::vec3>& vector);
	

private:

	glm::vec3 m_HighestVerticesValue, m_LowestVerticesValue;

	std::vector<uint32_t> m_VertexIndices, m_TextureIndices, m_NormalIndices;
	std::vector<glm::vec3> m_Vertices, m_Normals;
	std::vector<glm::vec2> m_TextureCoordinates;
	std::vector<float> rawVertices;
	std::vector<float> rawNormals;
	// Output variables
	std::vector<float> m_VertData; 
	std::vector<uint32_t> m_IndicesData; 


};

