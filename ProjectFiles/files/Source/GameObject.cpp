#include "GameObject.h"

GameObject::GameObject() : transform(glm::mat4(1.0f))
{
  
}

GameObject::~GameObject()
{
    m_IndexBuffer->Unbind();
    m_VertexBuffer->Unbind();
    m_VertexArray->Unbind();
}

void GameObject::SetPosition(float x, float y, float z)
{
    transform = glm::translate(glm::mat4(1.0f), glm::vec3(x,y,z));
}

glm::mat4 GameObject::GetTransform()
{
    return transform;
}

void GameObject::LoadModel(const std::string& path)
{
    // Create Mesh
    m_ModelMesh = std::make_unique<ModelMesh>(path);

    // Create Vertex Array
    m_VertexArray = std::make_unique<VertexArray>();

    // Vertex buffer object
    m_VertexBuffer = std::make_shared<VertexBuffer>(&m_ModelMesh->GetVertices()[0], m_ModelMesh->GetVertices().size() * sizeof(*m_ModelMesh->GetVertices().data()));

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
    m_IndexBuffer = std::make_shared<IndexBuffer>(&m_ModelMesh->GetIndecies()[0], m_ModelMesh->GetIndecies().size());
    m_VertexArray->AddIndexBuffer(m_IndexBuffer);

}

std::shared_ptr<IndexBuffer> GameObject::GetIndexBuffer() const
{
    return m_IndexBuffer;
}

std::shared_ptr<VertexArray> GameObject::GetVertexArray() const
{
    return m_VertexArray;
}
