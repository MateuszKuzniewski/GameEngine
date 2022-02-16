#pragma once
#include <string>
#include <glm.hpp>
#include <memory>
#include <gtc/quaternion.hpp>

#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ModelMesh.h"

struct Properties
{
	bool Gravity = true;
	bool Collisions = true;
};

class GameObject
{
public:

	GameObject();
	~GameObject();

	void SetPosition(float x, float y, float z);
	void LoadModel(const std::string& path);
	void GenerateQuad();
	void Update();

	glm::mat4 GetTransform() const;
	float GetWidth() const;
	float GetHeight() const;
	float GetDepth() const;
	std::shared_ptr<IndexBuffer> GetIndexBuffer() const;
	std::shared_ptr<VertexArray> GetVertexArray() const;
	Properties Properties;


private:

	void GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
	void Gravity();
	void BoxCollider();
	void UpdateTransform();

private:

	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<ModelMesh> m_ModelMesh;

	glm::mat4 transform;
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };

	float m_MinX, m_MinY, m_MinZ, m_MaxX, m_MaxY, m_MaxZ;
};

