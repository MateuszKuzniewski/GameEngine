#include "ModelMesh.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <algorithm>

ModelMesh::ModelMesh() : m_HighestVerticesValue(0), m_LowestVerticesValue(0)
{
	
}

ModelMesh::~ModelMesh()
{
	
}

void ModelMesh::ParseOBJ(const std::string& path)
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

void ModelMesh::ParseHeightMap(const std::string& path)
{

	int width, height, channels;
	unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, 0);

	float yScale = 128.0f / 256.0f;
	float yShift = 32.0f;

	for (uint32_t i = 0; i < height; i++)
	{
		for (uint32_t j = 0; j < width; j++)
		{
			unsigned char* texel = data + (j + width * i) * channels;
			unsigned char y = texel[0];
			glm::vec3 verts = glm::vec3(-width / 2.0f + j, (int)y * yScale - yShift, -height / 2.0f + i);
			m_Vertices.push_back(verts);
		}
	}
	stbi_image_free(data);

	for (uint32_t i = 0; i < height - 1; i++)
	{
		for (uint32_t j = 0; j < width; j++)
		{
			for (uint32_t k = 0; k < 2; k++)
			{
				m_VertexIndices.push_back(j + width * (i + k));
			}
		}
	}


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

		index++;
		m_IndicesData.push_back(index);
	}
}

void ModelMesh::Clear()
{ 
	m_Vertices.clear();
	m_Normals.clear();
	m_TextureCoordinates.clear();
	m_VertexIndices.clear();
	m_TextureIndices.clear();
	m_NormalIndices.clear();
	m_VertData.clear();
	m_IndicesData.clear();

}

void ModelMesh::CombineVertData(std::vector<glm::vec3>& vertices, std::vector<glm::vec3>& normals, std::vector<uint32_t>& vertIndices, std::vector<uint32_t>& normalIndices)
{
	m_HighestVerticesValue = CheckForHighestValue(vertices);
	m_LowestVerticesValue = CheckForLowestValue(vertices);
	
	uint32_t size = vertIndices.size();
	int index = 0;
	m_IndicesData.push_back(index);

	for (uint32_t i = 0; i < size; i++)
	{
		int indicesValue = vertIndices[i];
		glm::vec3 data = vertices[indicesValue];
		m_VertData.push_back(data.x);
		m_VertData.push_back(data.y);
		m_VertData.push_back(data.z);

		indicesValue = normalIndices[i];
		data = normals[indicesValue];
		m_VertData.push_back(data.x);
		m_VertData.push_back(data.y);
		m_VertData.push_back(data.z);

		index++;
		m_IndicesData.push_back(index);
		
	}
}

VectorComponents ModelMesh::GetVectorComponents(const std::vector<glm::vec3>& vector)
{
	/* Break down 2D Vector into separate 1D vectors to be able to access individual x,y,z components in those vectors */

	VectorComponents vectorComponents;
	std::vector<float> vertexComponent_X;
	std::vector<float> vertexComponent_Y;
	std::vector<float> vertexComponent_Z;

	for (uint32_t i = 0; i < vector.size(); i++)
	{
		glm::vec3 data = vector[i];
		vertexComponent_X.push_back(data.x);
		vertexComponent_Y.push_back(data.y);
		vertexComponent_Z.push_back(data.z);
	}

	vectorComponents.x = vertexComponent_X;
	vectorComponents.y = vertexComponent_Y;
	vectorComponents.z = vertexComponent_Z;

	return vectorComponents;
}

glm::vec3 ModelMesh::CheckForHighestValue(const std::vector<glm::vec3>& vector)
{
	VectorComponents vertexComponents = GetVectorComponents(vector);

	auto vertX = *std::max_element(std::begin(vertexComponents.x), std::end(vertexComponents.x));
	auto vertY = *std::max_element(std::begin(vertexComponents.y), std::end(vertexComponents.y));
	auto vertZ = *std::max_element(std::begin(vertexComponents.z), std::end(vertexComponents.z));

	
	return glm::vec3(vertX, vertY, vertZ);
}

glm::vec3 ModelMesh::CheckForLowestValue(const std::vector<glm::vec3>& vector)
{
	VectorComponents vertexComponents = GetVectorComponents(vector);

	auto vertX = *std::min_element(std::begin(vertexComponents.x), std::end(vertexComponents.x));
	auto vertY = *std::min_element(std::begin(vertexComponents.y), std::end(vertexComponents.y));
	auto vertZ = *std::min_element(std::begin(vertexComponents.z), std::end(vertexComponents.z));


	return glm::vec3(vertX, vertY, vertZ);
}


void ModelMesh::GenerateQuadData()
{

	std::vector<glm::vec3> vertPositions =
	{
		// x,y,z          
		glm::vec3(-5.0f, 0.0f, 0.0f), 
		glm::vec3( 5.0f, 0.0f, 0.0f),
		glm::vec3( 5.0f, 0.0f, 10.0f),
		glm::vec3(-5.0f, 0.0f, 10.0f)
	};


	std::vector<glm::vec3> vertNormals =
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

std::vector<uint32_t> ModelMesh::GetIndices() const
{
	return m_IndicesData;
}

std::vector<float> ModelMesh::GetVertices() const
{
	return m_VertData;
}

std::vector<float> ModelMesh::GetRawVertices()
{
	// returns array of vert coordinates without normals and UVs
	rawVertices.clear();
	for (int i = 0; i < m_Vertices.size(); i++)
	{
		glm::vec3 data = m_Vertices[i];
		rawVertices.push_back(data.x);
		rawVertices.push_back(data.y);
		rawVertices.push_back(data.z);
	}
	return rawVertices;
}

std::vector<float> ModelMesh::GetRawNormals()
{
	rawNormals.clear();
	for (int i = 0; i < m_Vertices.size(); i++)
	{
		glm::vec3 data = m_Normals[i];
		rawNormals.push_back(data.x);
		rawNormals.push_back(data.y);
		rawNormals.push_back(data.z);
	}
	return rawNormals;
}

std::vector<uint32_t> ModelMesh::GetRawIndices() const
{
	return m_VertexIndices;
}

glm::vec3 ModelMesh::GetHighestVert() const
{
	return m_HighestVerticesValue;
}

glm::vec3 ModelMesh::GetLowestVert() const
{
	return m_LowestVerticesValue;
}




