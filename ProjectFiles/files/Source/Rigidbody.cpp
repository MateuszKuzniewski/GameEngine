#include "Rigidbody.h"
#include <gtc/type_ptr.hpp>

Rigidbody::Rigidbody() : m_Rigidbody(NULL), m_Collider(NULL), isGravity(true)
{

}

Rigidbody::Rigidbody(const Component& componentData) : Component(componentData), m_Position(rp3d::Vector3(0.0f, 0.0f, 0.0f)), m_Collider(NULL), isGravity(true)
{
    m_Orientation = rp3d::Quaternion::identity();
    rp3d::Transform transform(m_Position, m_Orientation);
    m_Transform = transform;
    
    m_Rigidbody = m_PhysicsWorld->createRigidBody(m_Transform);

}

Rigidbody::~Rigidbody()
{   

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

rp3d::RigidBody* Rigidbody::GetRP3DRigidbody() const
{
    return m_Rigidbody;
}

rp3d::Vector3 Rigidbody::GetPosition() const
{
    return m_Rigidbody->getTransform().getPosition();
}

rp3d::Vector3 Rigidbody::GetEulerRotation() const
{   
    rp3d::Quaternion quat = m_Rigidbody->getTransform().getOrientation();
    glm::quat newQuat;

    newQuat.w = quat.w;
    newQuat.x = quat.x;
    newQuat.y = quat.y;
    newQuat.z = quat.z;

    glm::vec3 glmEulerAngles = glm::eulerAngles(newQuat);

    rp3d::Vector3 eulerAngles(glm::degrees(glmEulerAngles.x), glm::degrees(glmEulerAngles.y), glm::degrees(glmEulerAngles.z));
    return eulerAngles;
}

void Rigidbody::SetPosition(const rp3d::Vector3& position)
{
    m_Position = position;
    rp3d::Transform transform(m_Position, m_Rigidbody->getTransform().getOrientation());
    m_Rigidbody->setTransform(transform);
}

void Rigidbody::SetRotation(const rp3d::Vector3& rotation)
{  
    rp3d::Vector3 newVec(glm::radians(rotation.x), glm::radians(rotation.y), glm::radians(rotation.z));
    m_Orientation = rp3d::Quaternion::fromEulerAngles(newVec);
    rp3d::Transform transform(m_Rigidbody->getTransform().getPosition(), m_Orientation);
    m_Rigidbody->setTransform(transform);
    
}

rp3d::Transform Rigidbody::GetTransform() const
{
    return m_Rigidbody->getTransform();
}

glm::mat4 Rigidbody::GetOpenGLTransform() const
{
    rp3d::Transform pos = m_Rigidbody->getTransform();
    float mat[16];
    glm::mat4 matrix;
    pos.getOpenGLMatrix(mat);
    memcpy(glm::value_ptr(matrix), mat, sizeof(mat));

    return matrix;
}

std::string Rigidbody::GetBodyTypeString() const
{
    if (m_Rigidbody == nullptr) return "";

    auto type = m_Rigidbody->getType();
    switch (type)
    {
        case rp3d::BodyType::STATIC: return "static";
        case rp3d::BodyType::DYNAMIC: return "dynamic";
        case rp3d::BodyType::KINEMATIC: return "kinematic";
    }

    return "no body type available";
}

std::string Rigidbody::GetColliderTypeString() const
{
    if (m_Collider == nullptr) return "";

    auto type = m_Collider->getCollisionShape();
    switch (type->getName())
    {
        case rp3d::CollisionShapeName::BOX: return "box";
        case rp3d::CollisionShapeName::SPHERE: return "sphere";
        case rp3d::CollisionShapeName::TRIANGLE_MESH: return "mesh";
    }
    return "no collider type available";
}

void Rigidbody::AddBoxCollider(const rp3d::Vector3& halfPoints)
{
    rp3d::BoxShape* shape = m_PhysicsCommon->createBoxShape(halfPoints);
    m_Collider = m_Rigidbody->addCollider(shape, m_Transform);
    std::cout << "Box collider added" << std::endl;
}

void Rigidbody::AddSphereCollider(const float radius)
{
    rp3d::SphereShape* shape = m_PhysicsCommon->createSphereShape(radius);
    m_Collider = m_Rigidbody->addCollider(shape, m_Transform);
    std::cout << "Sphere collider added" << std::endl;
}

void Rigidbody::AddCapsuleCollider(const float radius, const float height)
{
    rp3d::CapsuleShape* shape = m_PhysicsCommon->createCapsuleShape(radius, height);
    m_Collider = m_Rigidbody->addCollider(shape, m_Transform);
    std::cout << "Capsule collider added" << std::endl;
    
}

void Rigidbody::AddConcaveColldier(const std::vector<float>& vertices, const std::vector<float>& normals, const std::vector<uint32_t>& indices)
//void Rigidbody::AddConcaveColldier(float* vertices, uint32_t* indices)
{
    m_Vertices.clear();
    m_Normals.clear();
    m_Indices.clear();

    m_Vertices.assign(vertices.begin(), vertices.end());
    m_Normals.assign(normals.begin(), normals.end());
    m_Indices.assign(indices.begin(), indices.end());

    uint32_t numberOfVertices = (m_Vertices.size() / 3);
    uint32_t numberOfTriangles = (m_Indices.size() / 3);

    rp3d::TriangleVertexArray* triangleArray = new rp3d::TriangleVertexArray(
        numberOfVertices,  &m_Vertices[0], 3 * sizeof(float),
        &m_Normals[0], 3 * sizeof(float),
        numberOfTriangles, &m_Indices[0], 3 * sizeof(uint32_t),
        rp3d::TriangleVertexArray::VertexDataType::VERTEX_FLOAT_TYPE, 
        rp3d::TriangleVertexArray::NormalDataType::NORMAL_FLOAT_TYPE,
        rp3d::TriangleVertexArray::IndexDataType::INDEX_INTEGER_TYPE);


    rp3d::TriangleMesh* triangleMesh = m_PhysicsCommon->createTriangleMesh();
    triangleMesh->addSubpart(triangleArray);
   
    rp3d::ConcaveMeshShape* shape = m_PhysicsCommon->createConcaveMeshShape(triangleMesh);
    m_Collider = m_Rigidbody->addCollider(shape, m_Transform);
    std::cout << "Mesh collider added" << std::endl;

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

