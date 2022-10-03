#pragma once
#include <vector>
#include <glm.hpp>
#include "Shader.h"
#include "VertexArray.h"

struct Particle
{
	glm::vec3 position;
	glm::vec3 rotation;
	glm::vec4 colour;
	float lifetime;

	Particle() : position(0.0f), rotation(0.0f), colour(1.0f), lifetime(0.0f) {}
};


class ParticleSystem
{
public:

	ParticleSystem(int numberOfParticles);
	~ParticleSystem();

	void Update(const float dt);
	void Render(const std::shared_ptr<Shader> shader);

private:

	void RespawnParticle(Particle& particle);


private:

	std::vector<Particle> m_particles;

	uint32_t m_maxNumberOfParticles;
	float m_defaultLifetime;

};

