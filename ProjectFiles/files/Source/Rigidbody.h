#pragma once
#include "Component.h"

class Rigidbody : public Component
{
public:
	Rigidbody();
	~Rigidbody();

private:
	rp3d::RigidBody* m_RigidBody;
};

