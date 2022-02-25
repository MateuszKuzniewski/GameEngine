#include "ModelMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

ModelMesh::ModelMesh(const std::string& path)
{
	std::ifstream inputStream(path);
	FILE* file = fopen(path.c_str(), "r");

	if (!inputStream) 
	{ 
		std::cerr << "Can't load model from a file " << path << std::endl; 
		exit(1); 
	}

	std::string line;
	while (std::getline(inputStream, line))
	{
		if (line.substr(0, 2) == "v ")
		{
			float x, y, z;
			std::istringstream stream(line.substr(2));
			glm::vec3 verticies;
			stream >> x;
			stream >> y;
			stream >> z;
			verticies = glm::vec3(x, y, z);
			m_Vertices.push_back(verticies);
		}
		else if (line.substr(0, 2) == "vt")
		{
			float u, v;
			std::istringstream stream(line.substr(3));
			glm::vec2 texCoordinates;
			stream >> u;
			stream >> v;
			texCoordinates = glm::vec2(u, v);
			m_TextureCoordinates.push_back(texCoordinates);
		}
		else if (line.substr(0, 2) == "vn")
		{
			float x, y, z;
			std::istringstream stream(line.substr(3));
			glm::vec3 normals;
			stream >> x;
			stream >> y;
			stream >> z;
			normals = glm::vec3(x, y, z);
			m_Normals.push_back(normals);
		}
		else if (line.substr(0, 2) == "f ")
		{
			int a, b, c; //to store mesh index
			int A, B, C; //to store texture index
			int na, nb, nc; //to store texture index

			const char* chh = line.c_str();
			sscanf(chh, "f %i/%i/%i %i/%i/%i %i/%i/%i", &a, &A, &na, &b, &B, &nb, &c, &C, &nc);


			a--; b--; c--;
			A--; B--; C--;
			na--; nb--; nc--;

			m_VertexIndices.push_back(a);
			m_VertexIndices.push_back(b);
			m_VertexIndices.push_back(c);

			m_TextureIndices.push_back(A);
			m_TextureIndices.push_back(B);
			m_TextureIndices.push_back(C);

			m_NormalIndices.push_back(na);
			m_NormalIndices.push_back(nb);
			m_NormalIndices.push_back(nc);
		}
	}

	CombineVertData(m_Vertices, m_Normals, m_VertexIndices, m_NormalIndices);
}

ModelMesh::~ModelMesh()
{

}


void ModelMesh::CombineVertData(std::vector<glm::vec3>& Vertices, std::vector<glm::vec3>& Normals, std::vector<uint32_t>& VertIndices, std::vector<uint32_t>& NormalIndices)
{
	m_HighestVerticesValue = CheckForHighestValue(Vertices);
	m_LowestVerticesValue = CheckForLowestValue(Vertices);
	
	uint32_t size = VertIndices.size();
	int index = 0;
	m_IndicesData.push_back(index);

	for (uint32_t i = 0; i < size; i++)
	{
		int indicesValue = VertIndices[i];
		glm::vec3 data = Vertices[indicesValue];
		m_VertData.push_back(data.x);
		m_VertData.push_back(data.y);
		m_VertData.push_back(data.z);

		indicesValue = NormalIndices[i];
		data = Normals[indicesValue];
		m_VertData.push_back(data.x);
		m_VertData.push_back(data.y);
		m_VertData.push_back(data.z);

		index++;
		m_IndicesData.push_back(index);
		
	}
}

glm::vec3 ModelMesh::CheckForHighestValue(const std::vector<glm::vec3>& vector)
{
	std::vector<float> vertexComponentX;
	std::vector<float> vertexComponentY;
	std::vector<float> vertexComponentZ;

	for (uint32_t i = 0; i < vector.size(); i++)
	{
		glm::vec3 data = vector[i];
		vertexComponentX.push_back(data.x);
		vertexComponentY.push_back(data.y);
		vertexComponentZ.push_back(data.z);
	}

	auto vertX = *std::max_element(std::begin(vertexComponentX), std::end(vertexComponentX));
	auto vertY = *std::max_element(std::begin(vertexComponentY), std::end(vertexComponentY));
	auto vertZ = *std::max_element(std::begin(vertexComponentZ), std::end(vertexComponentZ));

	
	return glm::vec3(vertX, vertY, vertZ);
}

glm::vec3 ModelMesh::CheckForLowestValue(const std::vector<glm::vec3>& vector)
{
	std::vector<float> vertexComponentX;
	std::vector<float> vertexComponentY;
	std::vector<float> vertexComponentZ;

	for (uint32_t i = 0; i < vector.size(); i++)
	{
		glm::vec3 data = vector[i];
		vertexComponentX.push_back(data.x);
		vertexComponentY.push_back(data.y);
		vertexComponentZ.push_back(data.z);
	}

	auto vertX = *std::min_element(std::begin(vertexComponentX), std::end(vertexComponentX));
	auto vertY = *std::min_element(std::begin(vertexComponentY), std::end(vertexComponentY));
	auto vertZ = *std::min_element(std::begin(vertexComponentZ), std::end(vertexComponentZ));


	return glm::vec3(vertX, vertY, vertZ);
}

void ModelMesh::GenerateQuadData()
{
	m_VertData.clear();
	m_IndicesData.clear();

	std::vector<glm::vec3>vertPositions =
	{
		// x,y,z          
		glm::vec3(-5.0f, 0.0f, 0.0f), 
		glm::vec3( 5.0f, 0.0f, 0.0f),
		glm::vec3( 5.0f, 0.0f, 10.0f),
		glm::vec3(-5.0f, 0.0f, 20.0f)
	};


	std::vector<glm::vec3>vertNormals =
	{
		// normals
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f),
		glm::vec3(0.0f, 1.0f, 0.0f)
	};


	std::vector<uint32_t> indices =
	{
		0, 1, 2,
		2, 3, 0
	};

	CombineVertData(vertPositions, vertNormals, indices, indices);

}

std::vector<uint32_t> ModelMesh::GetIndecies()
{
	return m_IndicesData;
}

std::vector<float> ModelMesh::GetVertices()
{
	return m_VertData;
}

glm::vec3 ModelMesh::GetHighestVert() const
{
	return m_HighestVerticesValue;
}

glm::vec3 ModelMesh::GetLowestVert() const
{
	return m_LowestVerticesValue;
}




