#pragma once
#include "Component.h"

class Collider
{
public:
	Collider() = default;
	~Collider();

	void SetPhysicsMaterial(rp3d::Material* material);
	rp3d::Material GetPhysicsMaterial();

private:

	rp3d::Material* m_Material;
};

