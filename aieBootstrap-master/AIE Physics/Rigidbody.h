#pragma once
#include <iostream>
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

	glm::vec2 ToWorld(glm::vec2 a_localPos);

	glm::vec2 GetPosition() { return m_position; }
	glm::vec2 GetVelocity() { return m_velocity; }

	float GetRotation() { return m_rotation; }
	void SetRotation(const float a_rotation) { m_rotation = a_rotation; }

	float GetMass() { return m_isKinematic ? INT_MAX : m_mass; }
	void SetMass(const float a_mass) { m_mass = a_mass; }

	float GetAngularVelocity() { return m_angularVelocity; }

	float GetMoment() { return m_isKinematic ? INT_MAX : m_moment; }

	bool GetIsKinematic() { return m_isKinematic; }
	void SetKinematic(bool a_state) { m_isKinematic = a_state; }

	float GetKineticEnergy();

	float ColourChange(float a_colour);

	float GetLinearDrag() { return m_linearDrag; }
	float SetLinearDrag(float a_linearDrag) { return m_linearDrag = a_linearDrag; }


	float GetAngularDrag() { return m_angularDrag; }
	float SetAngularDrag(float a_angularDrag) { return m_angularDrag = a_angularDrag; }


	void SetPosition(glm::vec2 a_position) {m_position = a_position; }

	void TriggerEnter(PhysicsObject* a_otherObject);
	//void TriggerExit(PhysicsObject* a_otherObject);

protected:

	glm::vec2 m_position;	
	glm::vec2 m_velocity;
	float m_rotation;
	float m_mass;
	float m_angularVelocity;
	float m_moment;
	float m_linearDrag;
	float m_angularDrag;

	//we will store the local x and y axes of the box based on its angle of rotation 
	glm::vec2 m_localX;
	glm::vec2 m_localY;

private:

};

