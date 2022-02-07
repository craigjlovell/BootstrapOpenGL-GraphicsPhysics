#include "Circle.h"
#include <Gizmos.h>
#include <glm/ext.hpp>

Circle::Circle(glm::vec2 a_position, glm::vec2 a_velocity,
	 float a_mass, float a_radius, glm::vec4 a_colour) : 
	Rigidbody(CIRCLE, a_position, a_velocity, 0, a_mass)
{
	m_radius = a_radius;
	m_colour = a_colour;
	m_isKinematic = false;
	m_moment = .5f * m_mass * a_radius * a_radius;
}

Circle::~Circle()
{

}

void Circle::MakeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_radius), std::sin(m_rotation)) * m_radius;

	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, glm::vec4(1,1,1,1));
}
