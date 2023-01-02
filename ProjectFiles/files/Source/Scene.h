#pragma once
#include "Renderer.h"
#include "Component.h"
#include "ObjectManager.h"

class Scene
{
public:
	Scene() {};
	virtual ~Scene() {};

	virtual void Begin(ObjectManager& objectManager, const Component& componentData) {};
	virtual void Update(const float dt, ObjectManager& objectManager) {};
	virtual void Render(const std::unique_ptr<Renderer>& renderer, const std::shared_ptr<Shader> shader, Camera& camera, ObjectManager& objectManager) {};

};


