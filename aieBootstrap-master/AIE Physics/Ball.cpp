#include "Ball.h"
#include <Gizmos.h>

Ball::Ball(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, BallType a_balls) : Circle(a_pos, a_vel ,a_mass, a_radius, a_colour)
{
	m_radius = a_radius;
	m_colour = a_colour;
	m_isKinematic = false;
	m_moment = 0.5f * m_mass * a_radius * a_radius;
	m_angularVelocity = 0;
	m_ballType = a_balls;
}


Ball::~Ball()
{

}

void Ball::MakeGizmo()
{
	glm::vec2 end = glm::vec2(std::cos(m_rotation), std::sin(m_rotation)) * m_radius;

	float r = ColourChange(m_colour.r);
	float g = ColourChange(m_colour.g);
	float b = ColourChange(m_colour.b);
	glm::vec4 invertColour(r, g, b, 1);

	aie::Gizmos::add2DCircle(m_position, m_radius, 12, m_colour);
	aie::Gizmos::add2DLine(m_position, m_position + end, invertColour);
}
