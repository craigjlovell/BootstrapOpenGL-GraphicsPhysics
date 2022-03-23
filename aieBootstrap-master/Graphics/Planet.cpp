#include "Planet.h"
#include "Gizmos.h"
#include "glm/glm.hpp"

Planet::Planet(glm::vec3 a_position, float a_size, glm::vec4 a_color, glm::vec3 a_rotation)
{
	//m_position = a_position;
	//m_size = a_size;
	//m_colour = a_color;
	//m_rotation = a_rotation;
}

Planet::~Planet()
{
}

void Planet::Update()
{
}

void Planet::CreatePlanet()
{
	aie::Gizmos::addSphere(m_position, m_size, 15, 15, m_colour);
}
