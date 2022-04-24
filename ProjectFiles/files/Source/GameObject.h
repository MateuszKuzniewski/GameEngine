#pragma once
#include <string>
#include <memory>
#include <typeinfo>
#include "Component.h"

class GameObject
{
public:
	GameObject();
	~GameObject();

	template<typename ComponentType, typename... Args>
	void AddComponent(Args&&... params);

	template<typename ComponentType>
	ComponentType& GetComponent();

	template<typename ComponentType>
	bool HasComponent();

private:

	std::vector<std::unique_ptr<Component>> m_Components;
	//std::unordered_map <uint32_t, std::unique_ptr<Component>> m_Components;

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
		if (component->GetComponentID() == std::make_unique<ComponentType>()->GetComponentID())
			return true;
	}

	return false;
}
