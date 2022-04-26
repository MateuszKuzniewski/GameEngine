#pragma once
#include "Component.h"
#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ModelMesh.h"


class MeshRenderer : public Component
{
public:
	MeshRenderer() = default;
	MeshRenderer(const Component& componentData);
	~MeshRenderer();

	void LoadFromOBJ(const std::string& path);
	void LoadFromHeightMap(const std::string& path);
	void GenerateQuad();
	std::shared_ptr<IndexBuffer> GetIndexBuffer() const;
	std::shared_ptr<VertexArray> GetVertexArray() const;

private:

	void GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);

private:


	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<ModelMesh> m_ModelMesh;



};

