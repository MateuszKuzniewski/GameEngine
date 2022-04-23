#include "Rigidbody.h"
#include <gtc/type_ptr.hpp>

Rigidbody::Rigidbody() : m_Rigidbody(NULL), m_Collider(NULL)
{

}

Rigidbody::Rigidbody(const Component& componentData) : Component(componentData), m_Position(rp3d::Vector3(0.0f, 0.0f, 0.0f)), m_Collider(NULL)
{
    m_Orientation = rp3d::Quaternion::identity();
    rp3d::Transform transform(m_Position, m_Orientation);
    m_Transform = transform;

    m_Rigidbody = m_PhysicsWorld->createRigidBody(m_Transform);
	m_ComponentID = 1;
}

Rigidbody::~Rigidbody()
{
    m_PhysicsWorld->destroyRigidBody(m_Rigidbody);
}

void Rigidbody::SetRigidbodyType(rp3d::BodyType type)
{
    m_Rigidbody->setType(type);
}

void Rigidbody::EnableGravity(bool state)
{
    m_Rigidbody->enableGravity(state);
}

void Rigidbody::ApplyForce(const rp3d::Vector3& force)
{
    m_Rigidbody->applyLocalForceAtCenterOfMass(force);
}

void Rigidbody::ApplyForceAtLocalPosition(const rp3d::Vector3& force, const rp3d::Vector3& point)
{
    m_Rigidbody->applyLocalForceAtLocalPosition(force, point);
}

void Rigidbody::ApplyTorque(const rp3d::Vector3& torque)
{
    m_Rigidbody->applyLocalTorque(torque);
}

rp3d::RigidBody* Rigidbody::GetRP3DRigidbody()
{
    return m_Rigidbody;
}

rp3d::Vector3 Rigidbody::GetPosition()
{
    return m_Rigidbody->getTransform().getPosition();
}

void Rigidbody::SetPositon(const rp3d::Vector3& position)
{
    m_Position = position;
    UpdateTransform();
}

void Rigidbody::SetRotation(const rp3d::Vector3& rotation)
{  
    rp3d::Vector3 newRotationInRadians(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
    rp3d::Quaternion newQuat = rp3d::Quaternion::fromEulerAngles(newRotationInRadians);
    m_Orientation = newQuat;
    UpdateTransform();
}

void Rigidbody::UpdateTransform()
{
    rp3d::Transform transform(m_Position, m_Orientation);
    m_Rigidbody->setTransform(transform);
}

rp3d::Transform Rigidbody::GetTransform()
{
    return m_Rigidbody->getTransform();
}

glm::mat4 Rigidbody::GetOpenGLTransform()
{
    rp3d::Transform pos = m_Rigidbody->getTransform();
    float mat[16];
    glm::mat4 matrix;
    pos.getOpenGLMatrix(mat);
    memcpy(glm::value_ptr(matrix), mat, sizeof(mat));

    return matrix;
}

void Rigidbody::AddBoxCollider(const rp3d::Vector3& halfPoints)
{
    rp3d::BoxShape* shape = m_PhysicsCommon->createBoxShape(halfPoints);
    m_Collider = m_Rigidbody->addCollider(shape, m_Transform);
}

void Rigidbody::AddSphereCollider(const float radius)
{
    rp3d::SphereShape* shape = m_PhysicsCommon->createSphereShape(radius);
    m_Collider = m_Rigidbody->addCollider(shape, m_Transform);
}

void Rigidbody::AddCapsuleCollider(const float radius, const float height)
{
    rp3d::CapsuleShape* shape = m_PhysicsCommon->createCapsuleShape(radius, height);
    m_Collider = m_Rigidbody->addCollider(shape, m_Transform);

}

void Rigidbody::SetPhysicalMaterialProperties(const float bounciness, const float friction)
{
    rp3d::Material& material = m_Collider->getMaterial();
    material.setBounciness(bounciness);
    material.setFrictionCoefficient(friction);
    m_Collider->setMaterial(material);

}

rp3d::Quaternion Rigidbody::CreateQuaternionFromEulerAngles(const rp3d::Vector3& angles)
{
    rp3d::Quaternion newQuat = rp3d::Quaternion::fromEulerAngles(angles);
    return newQuat;
}

