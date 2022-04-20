#pragma once
#include "Component.h"

class Collider : public Component
{
public:
	Collider(rp3d::RigidBody* rigidbody, rp3d::Transform transform);
	~Collider();

	void AddBoxCollider(const rp3d::Vector3& halfPoints);
	void AddSphereCollider(float radius);
	void AddCapsuleCollider(float radius, float height);
	rp3d::Material GetPhysicsMaterial();
	void SetPhysicsMaterial(float bounciness, float friction);

private:


	rp3d::Transform m_Transform;
	rp3d::Material* m_Material;
	rp3d::Collider* m_Collider;
	rp3d::RigidBody* m_Rigidbody;
};

