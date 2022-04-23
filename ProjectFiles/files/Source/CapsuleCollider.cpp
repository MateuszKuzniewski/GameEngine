#include "CapsuleCollider.h"

CapsuleCollider::CapsuleCollider(const Component& componentData, float radius, float height) : Component(componentData)
{
	rp3d::Vector3 position(0.0f, 0.0f, 0.0f);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(position, orientation);

	m_CollisionBody = m_PhysicsWorld->createCollisionBody(transform);
	rp3d::CapsuleShape* capsuleShape = m_PhysicsCommon->createCapsuleShape(radius, height);
	m_Collider = m_CollisionBody->addCollider(capsuleShape, transform);
	m_ComponentID = 3;
}

CapsuleCollider::~CapsuleCollider()
{
	m_PhysicsWorld->destroyCollisionBody(m_CollisionBody);
}
