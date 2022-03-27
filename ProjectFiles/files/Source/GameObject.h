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
#include "Time.h"

struct Properties
{
	bool Gravity = true;
	bool Collisions = true;
	bool hasCollided = false;
};

class GameObject
{
public:

	GameObject() = default;
	GameObject(const std::string& path, const std::string& name);
	~GameObject();

	void SetPosition(float x, float y, float z);
	void SetName(const std::string& name);
	void GenerateQuad();
	void Update();


	float GetWidth() const;
	float GetHeight() const;
	float GetDepth() const;
	std::string GetName() const;

	glm::mat4 GetTransform() const;
	glm::vec3 GetPosition() const;
	glm::vec3 GetVelocity() const;
	glm::vec2 GetWidthPoints() const;
	glm::vec2 GetHeightPoints() const;
	glm::vec2 GetDepthPoints() const;

	std::shared_ptr<IndexBuffer> GetIndexBuffer() const;
	std::shared_ptr<VertexArray> GetVertexArray() const;
	Properties Properties;


private:

	void GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
	void UpdateTransform();

private:

	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<ModelMesh> m_ModelMesh;

	glm::mat4 transform = glm::mat4(1.0f);
	glm::vec3 position = { 0.0f, 0.0f, 0.0f };
	glm::vec3 velocity = { 0.0f, 0.0f, 0.0f };
	std::string m_Name = "GameObject";

};

