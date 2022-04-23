#include "Collider.h"

// Destructor
Collider::~Collider() {

}

rp3d::Material Collider::GetPhysicsMaterial()
{
	return *m_Material;
}

void Collider::SetPhysicsMaterial(rp3d::Material* material)
{
	m_Material = material;

}
