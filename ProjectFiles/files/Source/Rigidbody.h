#pragma once
#include "Component.h"
#include "glm.hpp"

class Rigidbody : public Component
{
public:
	Rigidbody();
	Rigidbody(const Component& componentData);
	~Rigidbody();

	void SetRigidbodyType(rp3d::BodyType type);
	void SetPositon(const rp3d::Vector3& position); 
	void SetRotation(const rp3d::Vector3& rotation);

	void EnableGravity(bool state);
	void ApplyForce(const rp3d::Vector3& force);
	void ApplyForceAtLocalPosition(const rp3d::Vector3& force, const rp3d::Vector3& point);
	void ApplyTorque(const rp3d::Vector3& torque);
	rp3d::RigidBody* GetRP3DRigidbody();
	rp3d::Vector3 GetPosition();
	rp3d::Transform GetTransform();
	glm::mat4 GetOpenGLTransform();

	void AddBoxCollider(const rp3d::Vector3& halfPoints);
	void AddSphereCollider(const float radius);
	void AddCapsuleCollider(const float radius, const float height);
	void AddConcaveColldier(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<uint32_t>& indices);
	//void AddConcaveColldier(float* vertices, uint32_t* indices);
	void SetPhysicalMaterialProperties(const float bounciness, const float friction);

private:
	rp3d::Quaternion CreateQuaternionFromEulerAngles(const rp3d::Vector3& angles);
	void UpdateTransform();

private:
	rp3d::Vector3 m_Position;
	rp3d::Quaternion m_Orientation;
	rp3d::Vector3 m_EulerAngles;
	rp3d::Transform m_Transform;
	
	rp3d::RigidBody* m_Rigidbody;
	rp3d::Collider* m_Collider;
   
	// needed for creating concave mesh collider
	std::vector<float> m_Vertices;
	std::vector<float> m_Normals;
	std::vector<uint32_t> m_Indices;

};
