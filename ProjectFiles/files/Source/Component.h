#pragma once
#include <reactphysics3d/reactphysics3d.h>


class Component
{
public:
	Component() = default;
	Component(rp3d::PhysicsWorld* world, rp3d::PhysicsCommon* common);
	virtual ~Component();

protected:

	rp3d::PhysicsCommon* m_PhysicsCommon;
	rp3d::PhysicsWorld* m_PhysicsWorld;

};

