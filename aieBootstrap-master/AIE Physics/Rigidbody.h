#pragma once
#include <glm/glm.hpp>
#include <iostream>
#include <functional>
#include "PhysicsObject.h"


class Rigidbody : public PhysicsObject{
public:

	Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass);
	~Rigidbody();
	
	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep);
	virtual void Debug()
	{
		std::cout << "Positiom" << m_position.x << ', ' << m_position.y << std::endl;
	}

	void ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact, glm::vec2* a_collisionNormal = nullptr, float pen = 0);


	void ApplyForce(glm::vec2 a_force, glm::vec2 a_contact);
	//void ApplyForceToActor(Rigidbody* a_actor2, glm::vec2 a_force, glm::vec2 a_contact);

	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }

	float GetRotation() { return m_rotation; }
	void SetRotation(const float a_rotation) { m_rotation = a_rotation; }

	float GetMass() { return m_mass; }
	void SetMass(const float a_mass) { m_mass = a_mass; }

	float GetAngularVelocity() { return m_angularVelocity; }

	float GetMoment() { return m_moment; }

	bool GetIsKinematic() { return m_isKinematic; }

	float GetKineticEnergy();

protected:

	glm::vec2 m_position;	
	glm::vec2 m_velocity;
	float m_rotation;
	float m_mass;
	float m_angularVelocity;
	float m_moment;

private:

};

