#pragma once
#include <cstdint>

class IndexBuffer
{

public:

	IndexBuffer(const uint32_t* indices, const uint32_t count);
	~IndexBuffer();

	void Bind() const;
	void Unbind() const;

	uint32_t GetCount() const;

private:

	uint32_t m_count;
	uint32_t m_RendererID;
};

