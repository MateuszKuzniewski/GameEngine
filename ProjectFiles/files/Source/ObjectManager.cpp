#include "ObjectManager.h"

ObjectManager ObjectManager::s_Instance;

ObjectManager::ObjectManager() : m_IDCounter(0)
{
}

ObjectManager::~ObjectManager()
{
}

GameObject& ObjectManager::CreateGameObject()
{
	uint32_t id = m_IDCounter;
	m_IDCounter++;
	
	auto insertedObject = objectRegistry.emplace(id, std::make_shared<GameObject>(id));
	auto iterator = insertedObject.first;
	GameObject& createdObject = *iterator->second;
	return createdObject;
}

void ObjectManager::DestroyGameObject(const uint32_t id)
{
	objectRegistry.erase(id);
}
