#pragma once
#include <vector>
#include <string>
#include <cstdint>

enum class ShaderDataType
{
	None = 0, Float, Float2, Float3, Float4, Mat3, Mat4, Int, Int2, Int3, Int4, Bool
};

static uint32_t ShaderDataTypeSize(ShaderDataType type)
{
	switch (type)
	{
	case ShaderDataType::Float:    return 4;
	case ShaderDataType::Float2:   return 4 * 2;
	case ShaderDataType::Float3:   return 4 * 3;
	case ShaderDataType::Float4:   return 4 * 4;
	case ShaderDataType::Mat3:     return 4 * 3 * 3;
	case ShaderDataType::Mat4:     return 4 * 4 * 4;
	case ShaderDataType::Int:      return 4;
	case ShaderDataType::Int2:     return 4 * 2;
	case ShaderDataType::Int3:     return 4 * 3;
	case ShaderDataType::Int4:     return 4 * 4;
	case ShaderDataType::Bool:     return 1;
	}
	return 0;
}

struct BufferElementsLayout
{
	std::string Name;
	ShaderDataType Type;
	uint32_t Size;
	uint32_t Offset;
	bool Normalised;

	BufferElementsLayout(ShaderDataType type, const std::string& name, bool normalised = false)
		: Name(name), Type(type), Size(ShaderDataTypeSize(type)), Offset(0), Normalised(normalised) {}

	uint32_t GetComponentCount() const
	{
		switch (Type)
		{
			case ShaderDataType::Float:    return 1;
			case ShaderDataType::Float2:   return 2;
			case ShaderDataType::Float3:   return 3;
			case ShaderDataType::Float4:   return 4;
			case ShaderDataType::Mat3:     return 3 * 3;
			case ShaderDataType::Mat4:     return 4 * 4;
			case ShaderDataType::Int:      return 1;
			case ShaderDataType::Int2:     return 2;
			case ShaderDataType::Int3:     return 3;
			case ShaderDataType::Int4:     return 4;
			case ShaderDataType::Bool:     return 1;
		}
		return 0;
	}
};

class BufferLayout
{
public:

	BufferLayout() {}
	BufferLayout(const std::initializer_list<BufferElementsLayout>& element) 
	: m_Elements(element) 
	{
		CalculateOffsetAndStride();
	}

	uint32_t GetStride() const { return m_Stride; }
	const std::vector<BufferElementsLayout>& GetElement() const { return m_Elements; }

	std::vector<BufferElementsLayout>::const_iterator begin() const { return m_Elements.begin(); }
	std::vector<BufferElementsLayout>::const_iterator end()   const { return m_Elements.end(); }

	std::vector<BufferElementsLayout>::iterator begin() { return m_Elements.begin(); }
	std::vector<BufferElementsLayout>::iterator end()   { return m_Elements.end(); }

	

private:

	void CalculateOffsetAndStride()
	{
		uint32_t offset = 0;
		m_Stride = 0;
		for (auto& element : m_Elements)
		{
			element.Offset = offset;
			offset += element.Size;
			m_Stride += element.Size;
		}
	}

private:

	uint32_t m_Stride = 0;
	std::vector<BufferElementsLayout> m_Elements;

};

