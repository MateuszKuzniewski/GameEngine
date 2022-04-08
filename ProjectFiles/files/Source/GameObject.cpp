#include "GameObject.h"
#include <GLFW/glfw3.h>
#include <gtc/type_ptr.hpp>
#include <iostream>

GameObject::GameObject(rp3d::PhysicsWorld* world)
{
    m_Orientation = rp3d::Quaternion::identity();
    m_Transform = rp3d::Transform(m_Position, m_Orientation);
    m_RigidBody = world->createRigidBody(m_Transform);
    m_RigidBody->enableGravity(false);
    m_RigidBody->setType(rp3d::BodyType::STATIC);
}

GameObject::GameObject(const std::string& path, const std::string& name, rp3d::PhysicsWorld* world)
{
    Properties.name = name;
    m_ModelMesh = std::make_unique<ModelMesh>(path);
    GenerateBuffers(m_ModelMesh->GetVertices(), m_ModelMesh->GetIndices());
    m_Orientation = rp3d::Quaternion::identity();
    m_Transform = rp3d::Transform(m_Position, m_Orientation);
    m_RigidBody = world->createRigidBody(m_Transform);
}

GameObject::~GameObject()
{
    m_IndexBuffer->Unbind();
    m_VertexBuffer->Unbind();
    m_VertexArray->Unbind();
}


void GameObject::GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
{
    if (vertices.size() <= 0 || indices.size() <= 0)
    {
        std::cout << "GAME OBJECT: Cannot Generate Buffers... Missing Vertices or Indices Data" << std::endl;
        exit(1);
    }

     m_VertexArray = std::make_unique<VertexArray>();
     m_VertexBuffer = std::make_shared<VertexBuffer>(&vertices[0], vertices.size() * sizeof(*vertices.data()));
     m_IndexBuffer = std::make_shared<IndexBuffer>(&indices[0], indices.size());

     BufferLayout layout = {
         { ShaderDataType::Float3, "a_Position" },
         { ShaderDataType::Float3, "a_Normal"   }
         // { ShaderDataType::Float2, "a_TexCoord"}, 
         // { ShaderDataType::Float3, "a_Color" }

     };

     m_VertexBuffer->SetLayout(layout);
     m_VertexArray->AddVertexBuffer(m_VertexBuffer);
     m_VertexArray->AddIndexBuffer(m_IndexBuffer);
}

void GameObject::UpdateTransform(rp3d::RigidBody* body)
{
}

void GameObject::GenerateQuad()
{
    m_ModelMesh = std::make_unique<ModelMesh>();
    m_ModelMesh->GenerateQuadData();
    GenerateBuffers(m_ModelMesh->GetVertices(), m_ModelMesh->GetIndices());

}

void GameObject::SetPosition(const rp3d::Vector3& position)
{
    rp3d::Transform transform(position, m_RigidBody->getTransform().getOrientation());
    m_RigidBody->setTransform(transform);
}

void GameObject::SetRotation(const rp3d::Vector3& rotation)
{
    rp3d::Quaternion newRot = rp3d::Quaternion::fromEulerAngles(rotation);
    rp3d::Transform transform(m_RigidBody->getTransform().getPosition(), newRot);
    m_RigidBody->setTransform(transform);
}

void GameObject::AddSphereShape(rp3d::SphereShape* shape)
{
    m_Collider = m_RigidBody->addCollider(shape, m_Transform);
    rp3d::Material& material = m_Collider->getMaterial();
    material.setBounciness(0.9f);
    m_Collider->setMaterial(material);
}

void GameObject::AddBoxShape(rp3d::BoxShape* shape)
{
    m_Collider = m_RigidBody->addCollider(shape, m_Transform);

}

std::shared_ptr<IndexBuffer> GameObject::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

std::shared_ptr<VertexArray> GameObject::GetVertexArray() const
{
    return m_VertexArray;
}

glm::mat4 GameObject::GetOpenGLTransform() const
{
    rp3d::Transform pos = m_RigidBody->getTransform();
    float mat[16];
    glm::mat4 matrix;
    pos.getOpenGLMatrix(mat);
    memcpy(glm::value_ptr(matrix), mat, sizeof(mat));
   
    return matrix;
}

float GameObject::GetWidth() const
{
    float width = glm::distance(m_ModelMesh->GetLowestVert().x, m_ModelMesh->GetHighestVert().x);
    return width;
}

float GameObject::GetHeight() const
{
    float height = glm::distance(m_ModelMesh->GetLowestVert().y, m_ModelMesh->GetHighestVert().y);
    return height;
}

float GameObject::GetDepth() const
{
    float depth = glm::distance(m_ModelMesh->GetLowestVert().z, m_ModelMesh->GetHighestVert().z);
    return depth;
}

glm::vec2 GameObject::GetWidthPoints() const
{
    return glm::vec2(m_ModelMesh->GetLowestVert().x + m_RigidBody->getTransform().getPosition().x, m_ModelMesh->GetHighestVert().x + m_RigidBody->getTransform().getPosition().x);
}

glm::vec2 GameObject::GetHeightPoints() const
{
    return glm::vec2(m_ModelMesh->GetLowestVert().y + m_RigidBody->getTransform().getPosition().y, m_ModelMesh->GetHighestVert().y + m_RigidBody->getTransform().getPosition().y);
}

glm::vec2 GameObject::GetDepthPoints() const
{
    return glm::vec2(m_ModelMesh->GetLowestVert().z + m_RigidBody->getTransform().getPosition().z, m_ModelMesh->GetHighestVert().z + m_RigidBody->getTransform().getPosition().z);
}
