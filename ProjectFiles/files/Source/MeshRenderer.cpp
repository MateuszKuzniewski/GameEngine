#include "MeshRenderer.h"

MeshRenderer::MeshRenderer(const Component& componentData) : Component(componentData)
{

}

MeshRenderer::MeshRenderer(const Component& componentData, const std::string& path) : Component(componentData)
{
	m_ModelMesh = std::make_unique<ModelMesh>(path);
	GenerateBuffers(m_ModelMesh->GetVertices(), m_ModelMesh->GetIndices());

}

MeshRenderer::~MeshRenderer()
{
}

void MeshRenderer::GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices)
{
    if (vertices.size() <= 0 || indices.size() <= 0)
    {
        std::cout << "MESH RENDERER: Cannot Generate Buffers... Missing Vertices or Indices Data" << std::endl;
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

void MeshRenderer::GenerateQuad()
{
	m_ModelMesh = std::make_unique<ModelMesh>();
	m_ModelMesh->GenerateQuadData();
	GenerateBuffers(m_ModelMesh->GetVertices(), m_ModelMesh->GetIndices());
}

std::shared_ptr<IndexBuffer> MeshRenderer::GetIndexBuffer() const
{
	return m_IndexBuffer;
}

std::shared_ptr<VertexArray> MeshRenderer::GetVertexArray() const
{
	return m_VertexArray;
}

