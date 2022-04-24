#include "SphereCollider.h"

SphereCollider::SphereCollider(const Component& componentData, Rigidbody* rigidbody, float radius) : Component(componentData)
{
	rp3d::Vector3 position(0.0f, 0.0f, 0.0f);
	rp3d::Quaternion orientation = rp3d::Quaternion::identity();
	rp3d::Transform transform(position, orientation);

	m_CollisionBody = m_PhysicsWorld->createCollisionBody(transform);
	rp3d::SphereShape* sphereShape = m_PhysicsCommon->createSphereShape(radius);
	m_Collider = m_CollisionBody->addCollider(sphereShape, transform);


}

SphereCollider::~SphereCollider()
{
	m_PhysicsWorld->destroyCollisionBody(m_CollisionBody);
}
