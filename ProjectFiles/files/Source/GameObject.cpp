#include "GameObject.h"
#include <GLFW/glfw3.h>
#include <iostream>

GameObject::GameObject(const std::string& path) : transform(glm::mat4(1.0f))
{
    m_ModelMesh = std::make_unique<ModelMesh>(path);
    GenerateBuffers(m_ModelMesh->GetVertices(), m_ModelMesh->GetIndecies());
    UpdateTransform();
}

GameObject::~GameObject()
{
    m_IndexBuffer->Unbind();
    m_VertexBuffer->Unbind();
    m_VertexArray->Unbind();
}

void GameObject::SetPosition(float x, float y, float z)
{
    position += glm::vec3(x, y, z);
}



void GameObject::GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
{
    m_VertexArray = std::make_unique<VertexArray>();

     // Vertex buffer object
     m_VertexBuffer = std::make_shared<VertexBuffer>(&vertices[0], vertices.size() * sizeof(*vertices.data()));

     // Create layout
     BufferLayout layout = {
         { ShaderDataType::Float3, "a_Position" },
         { ShaderDataType::Float3, "a_Normal"   }
         // { ShaderDataType::Float2, "a_TexCoord"}, 
         // { ShaderDataType::Float3, "a_Color" }

     };

     // Vertex Array Object
     m_VertexBuffer->SetLayout(layout);
     m_VertexArray->AddVertexBuffer(m_VertexBuffer);

     // Index Buffer Object
     m_IndexBuffer = std::make_shared<IndexBuffer>(&indices[0], indices.size());
     m_VertexArray->AddIndexBuffer(m_IndexBuffer);
}

void GameObject::OnCollision()
{
}

void GameObject::Gravity()
{
    if (!Properties.Gravity)
        return;

    float g = 0.001f;

    const float deltaSpeed = g * Time::GetDeltaTime();
    position += deltaSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
}

void GameObject::BoxCollider(const std::shared_ptr<GameObject>& gobj)
{
    if (!Properties.Collisions)
        return;


}

void GameObject::UpdateTransform()
{
    transform = glm::translate(glm::mat4(1.0f), position);
}


void GameObject::GenerateQuad()
{
    m_ModelMesh = std::make_unique<ModelMesh>();
    m_ModelMesh->GenerateQuadData();
    GenerateBuffers(m_ModelMesh->GetVertices(), m_ModelMesh->GetIndecies());

}

void GameObject::Update()
{
    Gravity();
    UpdateTransform();
}


std::shared_ptr<IndexBuffer> GameObject::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

std::shared_ptr<VertexArray> GameObject::GetVertexArray() const
{
    return m_VertexArray;
}

glm::mat4 GameObject::GetTransform() const
{
    return transform;
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
    return glm::vec2(m_ModelMesh->GetLowestVert().x + position.x, m_ModelMesh->GetHighestVert().x + position.x);
}

glm::vec2 GameObject::GetHeightPoints() const
{
    return glm::vec2(m_ModelMesh->GetLowestVert().y + position.y, m_ModelMesh->GetHighestVert().y + position.y);
}

glm::vec2 GameObject::GetDepthPoints() const
{
    return glm::vec2(m_ModelMesh->GetLowestVert().z + position.z, m_ModelMesh->GetHighestVert().z + position.z);
}
