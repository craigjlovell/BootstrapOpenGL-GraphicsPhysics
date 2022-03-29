#pragma once
#include "glm/glm.hpp"

struct Particle
{
	glm::vec3 position;
	glm::vec3 velocity;
	glm::vec4 color;

	float size;
	float lifespan;
	float lifetime;

};

struct ParticleVertex
{
	glm::vec4 position;
	glm::vec4 color;
};

class ParticleEmitter
{
public:

	ParticleEmitter();
	virtual ~ParticleEmitter();

	void Inirialise(unsigned int a_maxParticles, unsigned int a_emitRate, 
		float a_lifetimeMin, float a_lifetimeMax,
		float a_velocityMin, float a_velocityMax, 
		float a_startSize, float a_endSize, 
		const glm::vec4& a_startColor, const glm::vec4& a_endColor);

	void Emit();
	void Update(float a_deltaTime, const glm::mat4& a_cameraTransform);
	void Draw();

	glm::vec3 GetPosition() { return m_position; }
	void SetPosition(glm::vec3 a_position) { m_position = a_position; };

protected:

	Particle*		m_particles;
	unsigned int	m_firstDead;
	unsigned int	m_maxParticles;

	unsigned int	m_vao, m_vbo, m_ibo;
	ParticleVertex* m_vertexData;

	glm::vec3		m_position;
	float			m_emitTimer;
	float			m_emitRate;

	float			m_lifespanMin;
	float			m_lifespanMax;

	float			m_velocityMin;
	float			m_velocityMax;

	float			m_startSize;
	float			m_endSize;

	glm::vec4		m_startColor;
	glm::vec4		m_endColor;

	glm::vec3		m_gravity = { 0,0,0 };
	bool			m_hasGravity = false;

};

