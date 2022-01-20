#pragma once
#include <cstdint>
#include "BufferLayout.h"

class VertexBuffer
{

public:

	VertexBuffer(const void* vertices, uint32_t size);
	~VertexBuffer();

	void Bind() const;
	void Unbind() const;

	void SetLayout(const BufferLayout& layout);
	const BufferLayout& GetLayout() const;


private:

	uint32_t m_RendererID;
	BufferLayout m_Layout;

};

