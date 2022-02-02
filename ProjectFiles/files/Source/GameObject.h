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


class GameObject
{
public:

	GameObject();
	~GameObject();

	void SetPosition(float x, float y, float z);
	glm::mat4 GetTransform();
	void LoadModel(const std::string& path);
	std::shared_ptr<IndexBuffer> GetIndexBuffer() const;
	std::shared_ptr<VertexArray> GetVertexArray() const;

private:

	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<ModelMesh> m_ModelMesh;

	glm::mat4 transform;

};

