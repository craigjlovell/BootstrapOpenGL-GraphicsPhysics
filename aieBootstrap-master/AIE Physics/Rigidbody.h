#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <iostream>
#include "PhysicsObject.h"


class Rigidbody : public PhysicsObject{
public:

	Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass);
	~Rigidbody() {};
	
	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Debug()
	{
		std::cout << "Positiom" << m_position.x << ', ' << m_position.y << std::endl;
	}

	virtual bool CheckCollision(PhysicsObject* pOther) = 0;

	void ApplyForce(glm::vec2 a_force);
	void ApplyForceToActor(Rigidbody* a_actor2, glm::vec2 a_force);

	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }
	float GetRotation() { return m_rotation; }
	float GetMass() { return m_mass; }
	void SetMass(const float a_mass) { m_mass = a_mass; }


protected:

	glm::vec2 m_position;	
	glm::vec2 m_velocity;
	float m_rotation;
	float m_mass;

private:

};

