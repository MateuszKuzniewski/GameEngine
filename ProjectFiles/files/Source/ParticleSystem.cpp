#include "ParticleSystem.h"
#include "GL/glew.h"
#include <time.h>

ParticleSystem::ParticleSystem(int numberOfParticles, const ParticleDirection& direction)
	: m_maxNumberOfParticles(300), m_defaultLifetime(1.0f), m_particleDirection(direction)
{

	float vertices[] = 
	{
		-0.5f, -0.5f, 0.0f,
		0.5f, -0.5f, 0.0f,
		0.5f,  0.5f, 0.0f,
		-0.5f,  0.5f, 0.0f
	};

	m_QuadVA = 0;
	glCreateVertexArrays(1, &m_QuadVA);
	glBindVertexArray(m_QuadVA);

	GLuint quadVB, quadIB;
	glCreateBuffers(1, &quadVB);
	glBindBuffer(GL_ARRAY_BUFFER, quadVB);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glEnableVertexArrayAttrib(quadVB, 0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), 0);

	uint32_t indices[] = 
	{
		0, 1, 2, 
		2, 3, 0
	};

	glCreateBuffers(1, &quadIB);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, quadIB);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	m_randomEngine.seed(std::random_device()());

	if (numberOfParticles <= m_maxNumberOfParticles)
	{
		m_particles.resize(numberOfParticles);

		for (uint32_t i = 0; i < m_particles.size(); i++)
		{
			RespawnParticle(m_particles[i]);
		}
	}
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::Update(const float dt)
{
	glm::vec3 dir = glm::vec3(0.0f, 0.0f, 0.0f);


	switch (m_particleDirection)
	{
		case ParticleDirection::UP:
			dir = glm::vec3(0.0f, -1.0f, 0.0f);
			break;
		case ParticleDirection::DOWN:
			dir = glm::vec3(0.0f, 1.0f, 0.0f);
			break;
		case ParticleDirection::LEFT:
			dir = glm::vec3(1.0f, 0.0f, 0.0f);
			break;
		case ParticleDirection::RIGHT:
			dir = glm::vec3(-1.0f, 0.0f, 0.0f);
			break;
	}

	for (uint32_t i = 0; i < m_particles.size(); i++)
	{

		m_particles[i].position -= dir * dt;
		m_particles[i].lifetime -= dt;

		if (m_particles[i].lifetime <= 0.0f)
		{
			RespawnParticle(m_particles[i]);
		}
	}
}

void ParticleSystem::RespawnParticle(Particle& particle)
{
	float offset = 10.0f;

	float random_x = (float)m_distribution(m_randomEngine) / (float)std::numeric_limits<uint32_t>::max() * offset;
	float random_y = (float)m_distribution(m_randomEngine) / (float)std::numeric_limits<uint32_t>::max() * offset;
	float random_z = (float)m_distribution(m_randomEngine) / (float)std::numeric_limits<uint32_t>::max() * offset;
	glm::vec3 pos = glm::vec3(random_x, random_y, random_z);
	glm::vec4 col = glm::vec4(random_x / offset, random_y / offset, random_z / offset, 1.0f);

	particle.position = pos;
	particle.colour = col;
	particle.lifetime = random_x;

}

void ParticleSystem::Render(const std::shared_ptr<Shader>& shader)
{
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	shader->Bind(); 
	for (auto& particle : m_particles)
	{
		glm::mat4 transform = glm::translate(glm::mat4(1.0f), { particle.position.x, particle.position.y, particle.position.z })
			* glm::rotate(glm::mat4(1.0f), particle.rotation, { 0.0f, 0.0f, 1.0f })
			* glm::scale(glm::mat4(1.0f), { particle.size.x, particle.size.y, 1.0f });

		shader->UploadUniformMat4("u_transform", transform);
		shader->UploadUniformFloat1("u_lifetime", particle.lifetime);
		shader->UploadUniformFloat4("u_particleColor", particle.colour);
		glBindVertexArray(m_QuadVA);

		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, nullptr);
	}
}

