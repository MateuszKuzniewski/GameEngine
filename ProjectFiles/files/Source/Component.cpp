#include "Component.h"

Component::Component(rp3d::PhysicsWorld* world, rp3d::PhysicsCommon* common) 
	: m_PhysicsWorld(world), m_PhysicsCommon(common), m_ComponentID(0)
{

}

Component::~Component()
{


}
