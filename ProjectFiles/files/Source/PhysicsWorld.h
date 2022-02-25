#pragma once
#include <vector>
#include "GameObject.h"


class PhysicsWorld
{
public:
	PhysicsWorld();
	~PhysicsWorld();

	void Update(const std::shared_ptr<GameObject>& gameObject_A, const std::shared_ptr<GameObject>& gameObject_B);


private:
	void CheckCollision(const std::shared_ptr<GameObject>& gameObject_A, const std::shared_ptr<GameObject>& gameObject_B);

private:
};

