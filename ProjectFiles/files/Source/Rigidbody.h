#pragma once
#include "Component.h"
#include "glm.hpp"

class Rigidbody : public Component
{
public:
	Rigidbody();
	Rigidbody(const Component& component);
	~Rigidbody();

	void SetRigidbodyType(rp3d::BodyType type);
	void SetPositon(const rp3d::Vector3& position); 
	void SetRotation(const rp3d::Vector3& rotation);

	void EnableGravity(bool state);
	void ApplyForce(const rp3d::Vector3& force);
	void ApplyForceAtLocalPosition(const rp3d::Vector3& force, const rp3d::Vector3& point);
	void ApplyTorque(const rp3d::Vector3& torque);

	rp3d::Vector3 GetPosition();
	rp3d::Transform GetTransform();
	glm::mat4 GetOpenGLTransform();

private:
	rp3d::Quaternion CreateQuaternionFromEulerAngles(const rp3d::Vector3& angles);
	void UpdateTransform();

private:
	rp3d::Vector3 m_Position;
	rp3d::Vector3 m_EulerAngles;
	rp3d::Quaternion m_Orientation;
	rp3d::Transform m_Transform;

	rp3d::RigidBody* m_Rigidbody;
};

