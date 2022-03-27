#include "PhysicsWorld.h"
#include <iostream>
#include <algorithm>
#include <time.h>

PhysicsWorld::PhysicsWorld()
{
	
}

PhysicsWorld::~PhysicsWorld()
{
}

void PhysicsWorld::Update()
{
	UpdateActiveObjects();
	CollisionBroadSearch();
}

void PhysicsWorld::Add(const std::shared_ptr<GameObject>& gameObject)
{
	if (gameObject.get() == nullptr)
	{
		std::cout << "PHYSICS WORLD: Trying to add object which is null" << std::endl;
		exit(1);
	}
	m_ActiveObjectsList.push_back(gameObject);
}


void PhysicsWorld::CheckCollision(const std::shared_ptr<GameObject>& gameObject_A, const std::shared_ptr<GameObject>& gameObject_B)
{
	if ((gameObject_A->GetWidthPoints().x  <= gameObject_B->GetWidthPoints().y  && gameObject_A->GetWidthPoints().y  >= gameObject_B->GetWidthPoints().x) &&
		(gameObject_A->GetHeightPoints().x <= gameObject_B->GetHeightPoints().y && gameObject_A->GetHeightPoints().y >= gameObject_B->GetHeightPoints().x) &&
		(gameObject_A->GetDepthPoints().x  <= gameObject_B->GetDepthPoints().y  && gameObject_A->GetDepthPoints().y  >= gameObject_B->GetDepthPoints().x))
	{
		gameObject_A->Properties.hasCollided = true;
		gameObject_B->Properties.hasCollided = true;
		//std::cout << "Collision: " << gameObject_A->GetName() << " + " << gameObject_B->GetName() << std::endl;
		CollisionResponse(gameObject_A, gameObject_B);
	}
	else
	{
		gameObject_A->Properties.hasCollided = false;
		gameObject_B->Properties.hasCollided = false;
	}
}

void PhysicsWorld::ApplyGravity(const std::shared_ptr<GameObject>& gameObject)
{

	glm::vec3 position = glm::vec3(0.0f);

	const float deltaSpeed = m_Gravity;
	position += deltaSpeed * glm::vec3(0.0f, -1.0f, 0.0f);
	gameObject->SetPosition(position.x, position.y, position.z);

}

void PhysicsWorld::UpdateActiveObjects()
{
	for (auto gameObject : m_ActiveObjectsList)
	{
		gameObject->Update();

		if (gameObject->Properties.Gravity)
			ApplyGravity(gameObject);
	}
}

std::vector<std::shared_ptr<GameObject>> PhysicsWorld::SortByMinX(std::vector<std::shared_ptr<GameObject>>& list)
{
	std::sort(list.begin(), list.end(),
		[=](std::shared_ptr<GameObject> object_A, std::shared_ptr<GameObject> object_B) -> bool 
		{
			return object_A->GetWidthPoints().x < object_B->GetWidthPoints().x; 
		});


	return list;
}


void PhysicsWorld::CollisionBroadSearch()
{
	m_ActiveObjectsList = SortByMinX(m_ActiveObjectsList);
	std::vector<std::shared_ptr<GameObject>> activeList;


	for (int i = 0; i < m_ActiveObjectsList.size(); ++i)
	{
		for (int j = 0; j < activeList.size(); ++j)
		{
			auto pos1 = m_ActiveObjectsList[i]->GetWidthPoints().x;
			auto pos2 = activeList[j]->GetWidthPoints().y;

			if (pos1 < pos2)
			{
				CheckCollision(m_ActiveObjectsList[i], activeList[j]);
				
			}
			else
			{
				activeList.erase(activeList.begin() + j);
				j--;
			}
		}
		activeList.push_back(m_ActiveObjectsList[i]);
	}
}

void PhysicsWorld::CollisionResponse(const std::shared_ptr<GameObject>& gameObject_A, const std::shared_ptr<GameObject>& gameObject_B)
{
	if (gameObject_A->Properties.hasCollided)
	{
		m_Gravity *= -1;
	}
}

void PhysicsWorld::AddImpulse(const std::shared_ptr<GameObject>& gameObject, glm::vec3 direction, float force)
{
	
}

