#include "ParticleSystemScene.h"

ParticleSystemScene::ParticleSystemScene()
{
}

ParticleSystemScene::~ParticleSystemScene()
{
}

void ParticleSystemScene::Begin(ObjectManager& objectManager, const Component& componentData)
{
	//m_particleSystem = std::make_shared<ParticleSystem>(100, ParticleDirection::DOWN);
}

void ParticleSystemScene::Update(const float dt, ObjectManager& objectManager)
{
	//m_particleSystem->Update(dt);
}

void ParticleSystemScene::Render(const std::unique_ptr<Renderer>& renderer, const std::shared_ptr<Shader> shader, Camera& camera, ObjectManager& objectManager)
{
	/*shader->UploadUniformMat4("u_projection", camera.GetProjectionMatrix());
	shader->UploadUniformMat4("u_viewMatrix", camera.GetViewMatrix());
	m_particleSystem->Render(shader);*/
}
