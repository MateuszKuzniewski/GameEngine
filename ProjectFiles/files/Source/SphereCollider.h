#pragma once
#include "Component.h"
#include "Collider.h"
#include "Rigidbody.h"

class SphereCollider : public Component
{
public:
	SphereCollider() = default;
	SphereCollider(const Component& componentData, Rigidbody* rigidbody, float radius);
	~SphereCollider();

private:

	rp3d::CollisionBody* m_CollisionBody;
	rp3d::Collider* m_Collider;

};

