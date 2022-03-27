#include "GameObject.h"
#include <GLFW/glfw3.h>
#include <iostream>

GameObject::GameObject(const std::string& path, const std::string& name) : transform(glm::mat4(1.0f))
{
    m_Name = name;
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

void GameObject::SetName(const std::string& name)
{
    m_Name = name;
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

glm::vec3 GameObject::GetPosition() const
{
    return position;
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

std::string GameObject::GetName() const
{
    return m_Name;
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
