#pragma once
#include <reactphysics3d/reactphysics3d.h>

class Component
{
public:
	Component() = default;
	Component(rp3d::PhysicsWorld* world, rp3d::PhysicsCommon* common);
	~Component();

	uint32_t GetComponentID() { return m_ComponentID; }

protected:

    uint32_t m_ComponentID;
	rp3d::PhysicsWorld* m_PhysicsWorld;
	rp3d::PhysicsCommon* m_PhysicsCommon;


};

