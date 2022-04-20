#include "Rigidbody.h"
#include <gtc/type_ptr.hpp>

Rigidbody::Rigidbody() : m_Rigidbody(NULL)
{

}
Rigidbody::Rigidbody(const Component& component) : Component(component), m_Position(rp3d::Vector3(0.0f,0.0f,0.0f))
{
    m_Orientation = rp3d::Quaternion::identity();
    rp3d::Transform transform(m_Position, m_Orientation);
    m_Transform = transform;
   
    m_Rigidbody = m_PhysicsWorld->createRigidBody(transform);
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
    rp3d::Quaternion newRotation = rp3d::Quaternion::fromEulerAngles(rotation);
    m_Orientation = newRotation;
    UpdateTransform();
}

void Rigidbody::UpdateTransform()
{
    rp3d::Transform transform(m_Position, m_Orientation);
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

rp3d::Quaternion Rigidbody::CreateQuaternionFromEulerAngles(const rp3d::Vector3& angles)
{
    rp3d::Quaternion newQuat = rp3d::Quaternion::fromEulerAngles(angles);
    return newQuat;
}

