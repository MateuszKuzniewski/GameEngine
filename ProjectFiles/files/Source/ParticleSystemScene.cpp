#include "ParticleSystemScene.h"

ParticleSystemScene::ParticleSystemScene()
{
}

ParticleSystemScene::~ParticleSystemScene()
{
}

void ParticleSystemScene::Begin(ObjectManager& objectManager, const Component& componentData)
{
	// Create 100 particles
	m_particleSystem = std::make_shared<ParticleSystem>(100);
}

void ParticleSystemScene::Update(const float dt)
{
	m_particleSystem->Update(dt);
}

void ParticleSystemScene::Render(const std::unique_ptr<Renderer>& renderer, const std::shared_ptr<Shader> shader, Camera& camera, ObjectManager& objectManager)
{
	m_particleSystem->Render(shader);
}
