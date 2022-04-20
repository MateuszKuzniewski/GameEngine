#pragma once
#include <string>
#include <glm.hpp>
#include <memory>

#include "IndexBuffer.h"
#include "BufferLayout.h"
#include "VertexBuffer.h"
#include "VertexArray.h"
#include "ModelMesh.h"
#include "Component.h"

class GameObject
{
public:
	GameObject() = default;
	GameObject(const std::string& path);
	~GameObject();

	void GenerateQuad();
	float GetWidth()  const;
	float GetHeight() const;
	float GetDepth()  const;

	glm::vec2 GetWidthPoints();
	glm::vec2 GetHeightPoints();
	glm::vec2 GetDepthPoints();

	std::shared_ptr<IndexBuffer> GetIndexBuffer() const;
	std::shared_ptr<VertexArray> GetVertexArray() const;

	template<typename ComponentType, typename... Args>
	void AddComponent(Args&&... params);

	template<typename ComponentType>
	ComponentType& GetComponent();

	template<typename ComponentType>
	bool HasComponent();

private:

	void GenerateBuffers(const std::vector<float>& vertices, const std::vector<uint32_t>& indices);

private:

	std::shared_ptr<IndexBuffer> m_IndexBuffer;
	std::shared_ptr<VertexBuffer> m_VertexBuffer;
	std::shared_ptr<VertexArray> m_VertexArray;
	std::unique_ptr<ModelMesh> m_ModelMesh;

	std::vector<std::unique_ptr<Component>> m_Components;

};

template<typename ComponentType, typename... Args>
inline void GameObject::AddComponent(Args&&... params)
{
	m_Components.emplace_back(std::make_unique<ComponentType>(std::forward< Args >(params)...));
}

template<typename ComponentType>
inline ComponentType& GameObject::GetComponent() 
{
	uint32_t componentIndex = 0;
	for (auto&& component : m_Components) 
	{
		componentIndex++;
		if (component->GetComponentID() == componentIndex)
			return *static_cast<ComponentType*>(component.get());
	}


	return *std::unique_ptr<ComponentType>(nullptr);
}

template<typename ComponentType>
inline bool GameObject::HasComponent()
{
	for (auto&& component : m_Components)
	{
		if (component->GetComponentID() == std::make_unique<ComponentType>()->GetComponentID())
			return true;
	}

	return false;
}
