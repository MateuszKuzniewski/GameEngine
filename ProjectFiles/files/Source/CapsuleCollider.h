#pragma once
#include "Component.h"
#include "Collider.h"


class CapsuleCollider : public Component
{
public:
	CapsuleCollider() = default;
	CapsuleCollider(const Component& componentData, float radius, float height);
	~CapsuleCollider();

private:

	rp3d::CollisionBody* m_CollisionBody;
	rp3d::Collider* m_Collider;
};


