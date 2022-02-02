#pragma once
#include "PhysicsObject.h"
//one sided object and is concidered to stand infintly along both sides of its edge and backwards from it normal direction


class Rigidbody;
class Plane : public PhysicsObject
{
public:

	Plane(glm::vec2 a_normal, float a_distanceToOrigin);
	Plane();
	~Plane();

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void MakeGizmo();
	virtual void Debug() {};
	virtual void ResetPosition() {};

	void ResolvePlaneCollision(Rigidbody* a_rigidbody, glm::vec2 a_contact);

	glm::vec2 GetNormal() { return m_normal; }
	float GetDistance() { return m_distanceToOrigin; }
	glm::vec4 GetColour() { return m_colour; }


protected:

	glm::vec2 m_normal;
	float m_distanceToOrigin;
	glm::vec4 m_colour;

private:

};

