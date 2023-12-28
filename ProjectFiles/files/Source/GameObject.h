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

	template<typename T, typename... Args>
	void AddComponent(Args&&... params);

	template<typename T>
	T& GetComponent();

	template<typename T>
	bool HasComponent();

	uint32_t GetID() const { return m_ID; };

	std::string name;
	bool isSelected;

private:
	uint32_t m_ID;
	std::vector<std::unique_ptr<Component>> m_Components;

};

template<typename T, typename... Args>
inline void GameObject::AddComponent(Args&&... params)
{
	m_Components.emplace_back(std::make_unique<T>(std::forward< Args >(params)...));
}

template<typename T>
inline T& GameObject::GetComponent() 
{
	for (auto&& component : m_Components) 
	{	
		// NOTE: Typeid returns human readible string in MSVC compiler, might not work on other compilers

		std::string tempTypeName = typeid(T).name();
		std::string ptrName = typeid(*component.get()).name();
		if (ptrName == tempTypeName)
			return *static_cast<T*>(component.get());
			
	}
	
	return *static_cast<T*>(nullptr);
}



template<typename T>
inline bool GameObject::HasComponent()
{
	for (auto&& component : m_Components)
	{
		// NOTE: Typeid returns human readible string in MSVC compiler, might not work on other compilers

		std::string tempTypeName = typeid(T).name();
		std::string ptrName = typeid(*component.get()).name();
		if (ptrName == tempTypeName)
			return true;


	}

	return false;
}
