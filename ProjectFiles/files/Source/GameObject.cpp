#include "GameObject.h"
#include <GLFW/glfw3.h>


GameObject::GameObject() : transform(glm::mat4(1.0f))
{
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

void GameObject::Gravity()
{
    if (!GameObjectProperties.Gravity)
        return;

    float g = 0.001f;
    float currentFrame = glfwGetTime();
    float lastFrame = 0.0f;
    float deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    const float deltaSpeed = g * deltaTime;
    position += deltaSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
}

void GameObject::UpdateTransform()
{
    transform = glm::translate(glm::mat4(1.0f), position);
}


void GameObject::LoadModel(const std::string& path)
{
    // Create Mesh
    m_ModelMesh = std::make_unique<ModelMesh>(path);
    GenerateBuffers(m_ModelMesh->GetVertices(), m_ModelMesh->GetIndecies());
}

void GameObject::GenerateQuad()
{
    std::vector<float> vertices =
    {
         // x,y,z           // normals
        -5.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         5.0f, 0.0f, 0.0f,  0.0f, 1.0f, 0.0f,
         5.0f, 0.0f, 5.0f,  0.0f, 1.0f, 0.0f,
        -5.0f, 0.0f, 5.0f,  0.0f, 1.0f, 0.0f
    };

    std::vector<uint32_t> indices =
    {
        0, 1, 2,
        2, 3, 0
    };

    GenerateBuffers(vertices, indices);

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
