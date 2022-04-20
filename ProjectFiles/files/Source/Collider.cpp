#include "Collider.h"

Collider::Collider(rp3d::RigidBody* rigidbody, rp3d::Transform transform) : m_Rigidbody(rigidbody), m_Transform(transform)
{
	//m_Material = &m_Collider->getMaterial();
	//m_ComponentID = 2;
}

Collider::~Collider()
{
}

//void Collider::AddBoxCollider(const rp3d::Vector3& halfPoints)
//{
//	rp3d::BoxShape* boxShape = m_PhysicsCommon->createBoxShape(halfPoints);
//	m_Collider = m_Rigidbody->addCollider(boxShape, m_Transform);
//}
//
//void Collider::AddSphereCollider(float radius)
//{
//	rp3d::SphereShape* sphereShape = m_PhysicsCommon->createSphereShape(radius);
//	m_Collider = m_Rigidbody->addCollider(sphereShape, m_Transform);
//}
//
//void Collider::AddCapsuleCollider(float radius, float height)
//{
//	rp3d::CapsuleShape* capsuleShape = m_PhysicsCommon->createCapsuleShape(radius, height);
//	m_Collider = m_Rigidbody->addCollider(capsuleShape, m_Transform);
//}
//
//rp3d::Material Collider::GetPhysicsMaterial()
//{
//	return *m_Material;
//}
//
//void Collider::SetPhysicsMaterial(float bounciness, float friction)
//{
//	m_Material->setBounciness(bounciness);
//	m_Material->setFrictionCoefficient(friction);
//	m_Collider->setMaterial(*m_Material);
//}
