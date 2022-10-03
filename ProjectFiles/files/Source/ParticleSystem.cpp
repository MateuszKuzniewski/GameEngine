#include "ParticleSystem.h"
#include "GL/glew.h"

ParticleSystem::ParticleSystem(int numberOfParticles) : m_maxNumberOfParticles(300), m_defaultLifetime(1.0f)
{
	if (numberOfParticles < m_maxNumberOfParticles)
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
	for (uint32_t i = 0; i < m_particles.size(); i++)
	{
		m_particles[i].position -= glm::vec3(0.0f, dt * 2.0f, 0.0f);
		m_particles[i].lifetime -= dt;

		if (m_particles[i].lifetime <= 0.0f)
		{
			RespawnParticle(m_particles[i]);
		}
	}
}

void ParticleSystem::RespawnParticle(Particle& particle)
{
	float random = ((rand() % 100) - 50) / 10.0f;
	glm::vec3 pos = glm::vec3(random, random, random);
	glm::vec4 col = glm::vec4(random, random, random, 1.0f);


	particle.position = pos;
	particle.colour = col;
	particle.lifetime = m_defaultLifetime;
}

void ParticleSystem::Render(const std::shared_ptr<Shader> shader)
{
	uint32_t vertexBuffer = 0;

	std::vector< float > vertices;
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(0.0f);
	vertices.push_back(0.0f);

	vertices.push_back(1.0f);
	vertices.push_back(1.0f);
	vertices.push_back(0.0f);

	glGenBuffers(1, &vertexBuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), vertices.data(), GL_STATIC_DRAW);


	shader->Bind();

	for (uint32_t i = 0; i < m_particles.size(); i++)
	{
		glEnableVertexAttribArray(0);

		shader->UploadUniformVec3("u_position", m_particles[i].position);
		shader->UploadUniformFloat4("u_color", m_particles[i].colour);

		glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
		glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}
}

