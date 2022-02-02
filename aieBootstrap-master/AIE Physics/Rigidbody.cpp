#include "Rigidbody.h"

Rigidbody::Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_rotation = a_rotation;
	m_mass = a_mass;
}

void Rigidbody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	m_position += GetVelocity() * a_timeStep;
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0));

	m_rotation += m_angularVelocity * a_timeStep;
}

void Rigidbody::ResolveCollision(Rigidbody* a_actor2)
{
	glm::vec2 normal = glm::normalize(a_actor2->GetPosition() - m_position);
	glm::vec2 relativeVelocity = a_actor2->GetVelocity() - m_velocity;

	float elasticity = 1;
	//Impulse magnitude
	float j = glm::dot(- (1 + elasticity) * relativeVelocity, normal) / ((1 / m_mass) + (1 / a_actor2->GetMass()));

	glm::vec2 force = normal * j;

	float kePre = GetKineticEnergy();
	float otherkePre = a_actor2->GetKineticEnergy();

	//ApplyForceToActor(a_actor2, force, GetPosition());

	std::cout << "KE" << kePre << ", " << otherkePre << std::endl;
}

bool Rigidbody::CheckCollision(PhysicsObject* pOther)
{
	return false;
}

void Rigidbody::ApplyForce(glm::vec2 a_force, glm::vec2 a_contact)
{
	m_velocity += a_force / GetMass();
	m_angularVelocity += (a_force.y * a_contact.x - a_force.x * a_contact.y) / GetMoment();
}

//void Rigidbody::ApplyForceToActor(Rigidbody* a_actor2, glm::vec2 a_force, glm::vec2 a_contact)
//{
//	ApplyForce(-a_force, a_contact);
//	a_actor2->ApplyForce(a_force, a_contact);
//}

float Rigidbody::GetKineticEnergy()
{
	float totalEnergy = (m_mass * glm::dot(m_velocity, m_velocity)) / 2;

	return totalEnergy;
}
