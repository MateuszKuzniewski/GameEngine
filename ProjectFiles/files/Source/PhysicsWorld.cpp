#include "PhysicsWorld.h"
#include <iostream>

PhysicsWorld::PhysicsWorld()
{
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::Update(const std::shared_ptr<GameObject>& gameObject_A, const std::shared_ptr<GameObject>& gameObject_B)
{
	CheckCollision(gameObject_A, gameObject_B);
}


void PhysicsWorld::CheckCollision(const std::shared_ptr<GameObject>& gameObject_A, const std::shared_ptr<GameObject>& gameObject_B)
{
	if ((gameObject_A->GetWidthPoints().x  <= gameObject_B->GetWidthPoints().y  && gameObject_A->GetWidthPoints().y  >= gameObject_B->GetWidthPoints().x) &&
		(gameObject_A->GetHeightPoints().x <= gameObject_B->GetHeightPoints().y && gameObject_A->GetHeightPoints().y >= gameObject_B->GetHeightPoints().x) &&
		(gameObject_A->GetDepthPoints().x  <= gameObject_B->GetDepthPoints().y  && gameObject_A->GetDepthPoints().y  >= gameObject_B->GetDepthPoints().x))
	{
		std::cout << "Collision" << std::endl;
	}
}
