#pragma once
#include "Circle.h"
class Ball : public Circle
{
public:

	Ball(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, BallType a_balls);
	~Ball ();
	
	void MakeGizmo();
	float GetRadius() { return m_radius; }
	glm::vec4 GetColour() { return m_colour; }
protected:
	float m_radius;
	glm::vec4 m_colour;
};

