#include "ModelMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>

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
			m_Verticies.push_back(verticies);
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
		else if (line.substr(0, 2) == "f ")
		{
			int a, b, c; //to store mesh index
			int A, B, C; //to store texture index

			const char* chh = line.c_str();
			sscanf(chh, "f %i/%i %i/%i %i/%i", &a, &A, &b, &B, &c, &C);

			a--; b--; c--;
			A--; B--; C--;

			m_Indecies.push_back(a);
			m_Indecies.push_back(b);
			m_Indecies.push_back(c);
		}
	}
	CombineVertData();
}

ModelMesh::~ModelMesh()
{

}

void ModelMesh::CombineVertData()
{
	//int size = 20000;
	int size = m_Verticies.size();

	for (int i = 0; i < size; i++)
	{
		float data = 0.0f;
		data = m_Verticies[i].x;
		m_VertData.push_back(data);

		data = m_Verticies[i].y;
		m_VertData.push_back(data);

		data = m_Verticies[i].z;
		m_VertData.push_back(data);


		data = m_TextureCoordinates[i].x;
		m_VertData.push_back(data);

		data = m_TextureCoordinates[i].y;
		m_VertData.push_back(data);
	}
}

std::vector<uint32_t> ModelMesh::GetIndecies()
{
	return m_Indecies;
}

std::vector<float> ModelMesh::GetVertices()
{
	return m_VertData;
}

std::vector<glm::vec2> ModelMesh::GetTexCoord() const
{
	return m_TextureCoordinates;
}

int ModelMesh::GetVerticiesArraySize()
{
	return m_VertData.size();
}

