#pragma once
#include <cstdint>
#include <unordered_map>
#include "GameObject.h"

class ObjectManager
{
public:

	ObjectManager(const ObjectManager&) = delete;

	static ObjectManager& GetInstance()
	{
		return s_Instance;
	}

	GameObject& CreateGameObject();
	void DestroyGameObject(const uint32_t id);
	std::unordered_map<uint32_t, std::shared_ptr<GameObject>> objectRegistry;

private:
	ObjectManager();
	~ObjectManager();

	uint32_t m_IDCounter;


	static ObjectManager s_Instance;
};

