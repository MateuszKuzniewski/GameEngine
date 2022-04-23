#pragma once
#include "Component.h"
#include "Collider.h"
#include "Rigidbody.h"


class BoxCollider : public Component
{
public:
	BoxCollider() = default;
	BoxCollider(const Component& componentData, Rigidbody* rigidbody, const rp3d::Vector3& halfPoints);
	~BoxCollider();

private:
	
	rp3d::CollisionBody* m_CollisionBody;
	rp3d::Collider* m_Collider;
};

