#pragma once
#include "Scene.h"
#include "EnginePaths.h"
#include "ComponentTypes.h"

class DefaultScene : public Scene
{
public:
	DefaultScene();
	~DefaultScene();

	void Begin(ObjectManager& objectManager, const Component& componentData) override;
	void Update(const float dt, ObjectManager& objectManager) override;
	void Render(const std::unique_ptr<Renderer>& renderer, const std::shared_ptr<Shader> shader, Camera& camera, ObjectManager& objectManager) override;

private:

	std::shared_ptr<Shader> m_particleShader;
};

