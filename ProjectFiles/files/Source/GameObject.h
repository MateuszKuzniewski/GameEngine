#pragma once
#include <string>
#include <glm.hpp>
#include <memory>
#include <gtc/quaternion.hpp>
#include <reactphysics3d/reactphysics3d.h>

#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ModelMesh.h"
#include "Time.h"
#include "Component.h"

struct Properties
{
	std::string name = "GameObject";
	bool gravity = true;
	bool collisions = true;
	bool hasCollided = false;
};

class GameObject
{
public:
	GameObject() = default;
	GameObject(rp3d::PhysicsWorld* world);
	GameObject(const std::string& path, const std::string& name, rp3d::PhysicsWorld* world);
	~GameObject();

	void GenerateQuad();
	void SetPosition(const rp3d::Vector3& position);
	void SetRotation(const rp3d::Vector3& rotation);
	void AddSphereShape(rp3d::SphereShape* shape);
	void AddBoxShape(rp3d::BoxShape* shape);
	float GetWidth() const;
	float GetHeight() const;
	float GetDepth() const;

	glm::mat4 GetOpenGLTransform() const;
	glm::vec2 GetWidthPoints() const;
	glm::vec2 GetHeightPoints() const;
	glm::vec2 GetDepthPoints() const;

	std::shared_ptr<IndexBuffer> GetIndexBuffer() const;
	std::shared_ptr<VertexArray> GetVertexArray() const;
	
	// Public Handles
	Properties Properties;

private:

	void GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);
	void UpdateTransform(rp3d::RigidBody* body);

private:

	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<ModelMesh> m_ModelMesh;

	rp3d::Quaternion m_Orientation;
	rp3d::Transform m_Transform;
	rp3d::Vector3 m_Position;
	rp3d::RigidBody* m_RigidBody;
	rp3d::Collider* m_Collider;
};

