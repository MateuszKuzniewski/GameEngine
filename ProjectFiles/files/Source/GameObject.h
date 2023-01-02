#pragma once
#include <string>
#include <memory>
#include <typeinfo>
#include "Component.h"

class GameObject
{
public:
	GameObject(uint32_t id);
	~GameObject();

	template<typename ComponentType, typename... Args>
	void AddComponent(Args&&... params);

	template<typename ComponentType>
	ComponentType& GetComponent();

	template<typename ComponentType>
	bool HasComponent();

	uint32_t GetID() const { return m_ID; };

	std::string name;
	bool isSelected;

private:
	uint32_t m_ID;
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
	for (auto&& component : m_Components) 
	{	
		// NOTE: Typeid returns human readible string in MSVC compiler, might not work on other compilers

		std::string tempTypeName = typeid(ComponentType).name();
		std::string ptrName = typeid(*component.get()).name();
		if (ptrName == tempTypeName)
			return *static_cast<ComponentType*>(component.get());
			
	}
	
	return *static_cast<ComponentType*>(nullptr);
}



template<typename ComponentType>
inline bool GameObject::HasComponent()
{
	for (auto&& component : m_Components)
	{
		// NOTE: Typeid returns human readible string in MSVC compiler, might not work on other compilers

		std::string tempTypeName = typeid(ComponentType).name();
		std::string ptrName = typeid(*component.get()).name();
		if (ptrName == tempTypeName)
			return true;


	}

	return false;
}
