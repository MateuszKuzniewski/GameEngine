#pragma once
#include <cstdint>
#include <vector>
#include <memory>

#include "IndexBuffer.h"
#include "VertexBuffer.h"

class VertexArray
{
public:

	VertexArray();
	~VertexArray();

	void Bind() const;
	void Unbind() const;

	void AddVertexBuffer(const std::shared_ptr<VertexBuffer>& vertexBuffer);
	void AddIndexBuffer(const std::shared_ptr<IndexBuffer>& indexBuffer);

private:

	std::vector <std::shared_ptr<VertexBuffer>> m_VertexBuffer;
	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	uint32_t m_RendererID;

};

