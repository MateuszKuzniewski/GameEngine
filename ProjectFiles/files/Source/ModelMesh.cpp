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
			m_HighestVerticesValue = CheckForHighestValue(verticies);
			m_LowestVerticesValue = CheckForLowestValue(verticies);
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
	CombineVertData();
}

ModelMesh::~ModelMesh()
{

}

void ModelMesh::CombineVertData()
{
	uint32_t size = m_VertexIndices.size();
	int index = 0;
	m_IndicesData.push_back(index);

	for (uint32_t i = 0; i < size; i++)
	{
		int indicesValue = m_VertexIndices[i];
		glm::vec3 data = m_Vertices[indicesValue];
		m_VertData.push_back(data.x);
		m_VertData.push_back(data.y);
		m_VertData.push_back(data.z);

		indicesValue = m_NormalIndices[i];
		data = m_Normals[indicesValue];
		m_VertData.push_back(data.x);
		m_VertData.push_back(data.y);
		m_VertData.push_back(data.z);

		index++;
		m_IndicesData.push_back(index);
		
	}

}

glm::vec3 ModelMesh::CheckForHighestValue(glm::vec3 values)
{
	if (values.x > m_Temp.x)
		m_Temp.x = values.x;
	if (values.y > m_Temp.y)
		m_Temp.y = values.y;
	if (values.z > m_Temp.z)
		m_Temp.z = values.z;

	
	return m_Temp;
}

glm::vec3 ModelMesh::CheckForLowestValue(glm::vec3 values)
{
	if (values.x < m_TempLowest.x)
		m_TempLowest.x = values.x;
	if (values.y < m_TempLowest.y)
		m_TempLowest.y = values.y;
	if (values.z < m_TempLowest.z)
		m_TempLowest.z = values.z;


	return m_TempLowest;
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


