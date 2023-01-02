#pragma once
#include "GL/glew.h"
#include "Component.h"
#include "Shader.h"
#include <vector>
#include <glm.hpp>
#include <memory>
#include <random>

enum class ParticleDirection
{
	UP,
	DOWN,
	LEFT,
	RIGHT
};

class ParticleSystem : public Component
{
public:

	struct Particle
	{
		glm::vec3 position;
		glm::vec3 size;
		glm::vec4 colour;
		float rotation;
		float lifetime;

		Particle() : position(0.0f), rotation(0.0f), size(1.0f), colour(1.0f), lifetime(1.0f) {}
	};

	ParticleSystem(const Component& componentData, int numberOfParticles, const ParticleDirection& direction);
	~ParticleSystem();

	void Update(const float dt);
	void Render(const std::shared_ptr<Shader>& shader);


private:

	void RespawnParticle(Particle& particle);


private:

	std::vector<Particle> m_particles;
	std::vector<float> vertices;

	uint32_t m_maxNumberOfParticles;
	float m_defaultLifetime;

	ParticleDirection m_particleDirection;

	GLuint m_QuadVA = 0;
	Particle particle;
	std::mt19937 m_randomEngine;
	std::uniform_int_distribution<std::mt19937::result_type> m_distribution;

};

