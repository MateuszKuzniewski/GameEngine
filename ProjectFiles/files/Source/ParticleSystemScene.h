#pragma once
#include "Scene.h"
#include "ParticleSystem.h"
#include <memory>

class ParticleSystemScene : public Scene
{
public:

	ParticleSystemScene();
	~ParticleSystemScene();

	void Begin(ObjectManager& objectManager, const Component& componentData) override;
	void Update(const float dt, ObjectManager& objectManager) override;
	void Render(const std::unique_ptr<Renderer>& renderer, const std::shared_ptr<Shader> shader, Camera& camera, ObjectManager& objectManager) override;

private:

	std::shared_ptr<ParticleSystem> m_particleSystem;
};

