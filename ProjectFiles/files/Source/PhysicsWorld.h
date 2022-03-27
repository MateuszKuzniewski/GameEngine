#pragma once
#include <vector>
#include "GameObject.h"


class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void Update();
	void Add(const std::shared_ptr<GameObject>& gameObject);

private:
	void CheckCollision(const std::shared_ptr<GameObject>& gameObject_A, const std::shared_ptr<GameObject>& gameObject_B);
	void ApplyGravity(const std::shared_ptr<GameObject>& gameObject);
	void UpdateActiveObjects();
	void CollisionBroadSearch();
	std::vector<std::shared_ptr<GameObject>> SortByMinX( std::vector<std::shared_ptr<GameObject>>& list);

private:
	std::vector<std::shared_ptr<GameObject>> m_ActiveObjectsList;

};

