#include "BoxCollider.h"

BoxCollider::BoxCollider(const Component& componentData, Rigidbody* rigidbody, const rp3d::Vector3& halfPoints) : Component(componentData)
{
	rp3d::Vector3 position(0.0f, -5.0f, -5.0f);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(position, orientation);

	m_CollisionBody = m_PhysicsWorld->createCollisionBody(transform);
	rp3d::BoxShape* boxShape = m_PhysicsCommon->createBoxShape(halfPoints);
	m_Collider = m_CollisionBody->addCollider(boxShape, transform);
	m_ComponentID = 2;
}

BoxCollider::~BoxCollider()
{
	m_PhysicsWorld->destroyCollisionBody(m_CollisionBody);
}
