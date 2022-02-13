#include "Plane.h"
#include "Rigidbody.h"
#include "PhysicsScene.h"
#include <glm/glm.hpp>
#include <Gizmos.h>

Plane::Plane(glm::vec2 a_normal, float a_distanceToOrigin) : PhysicsObject(PLANE)
{
	m_normal = a_normal;
	m_distanceToOrigin = a_distanceToOrigin;
	m_colour = glm::vec4(0, 1, 0, 1);
	m_isKinematic = true;
	m_isTrigger = false;
	m_elasticity = 1;
}

Plane::Plane(glm::vec2 a_normal, float a_distanceToOrigin, glm::vec4 a_colour) : PhysicsObject(PLANE)
{
	m_normal = a_normal;
	m_distanceToOrigin = a_distanceToOrigin;
	m_colour = glm::vec4(0, 1, 0, 1);
	m_isKinematic = true;
	m_isTrigger = false;
	m_elasticity = 1;
}

Plane::Plane() : PhysicsObject(PLANE)
{
	m_normal = glm::vec2(0,1);
	m_distanceToOrigin = 0;
	m_colour = glm::vec4(1,1,1,1);
	m_isKinematic = true;
	m_isTrigger = false;
	m_elasticity = 1;
}

Plane::~Plane()
{

}

void Plane::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{

}

void Plane::MakeGizmo()
{
	float LineSegmentLength = 300;

	glm::vec2 centerPoint = m_normal * m_distanceToOrigin;
	glm::vec2 parallel(m_normal.y, -m_normal.x);
	glm::vec4 colourFade = m_colour;

	colourFade.a = 0;

	glm::vec2 start = centerPoint + (parallel * LineSegmentLength);
	glm::vec2 end = centerPoint - (parallel * LineSegmentLength);

	aie::Gizmos::add2DLine(start, end, glm::vec4(1,0,1,1));
	aie::Gizmos::add2DTri(start, end, start - m_normal * 10.f, m_colour, m_colour, colourFade);
	aie::Gizmos::add2DTri(end, end - m_normal * 10.f, start - m_normal * 10.f, m_colour, glm::vec4(0, 0, 1, 1), glm::vec4(1, 0, 0, 1));
}

void Plane::ResolvePlaneCollision(Rigidbody* a_rigidbody, glm::vec2 a_contact)
{
	//the position at witch we'll apply the force relative to the objet's center of mass
	glm::vec2 localContact = a_contact - a_rigidbody->GetPosition();

	//the plane will not move so the relative velocity is just the rigidbody's velocity at the contact point
	glm::vec2 vRel = a_rigidbody->GetVelocity() + a_rigidbody->GetAngularVelocity() * glm::vec2(-localContact.y, localContact.x);

	float velocityIntoPlane = glm::dot(vRel, m_normal);

	//perfect elasticity collision [ToBeUpdated]
	float e = (GetElasticity() + a_rigidbody->GetElasticity())/ 2;

	// find the perpendicular distance so we can apply force at the relative
	// center of mass, torque= f*r
	float r = glm::dot(localContact, glm::vec2(m_normal.y, -m_normal.x));


	if (!m_isTrigger && !a_rigidbody->IsTrigger())
	{
		// determine the 'effective mass' - this is the combination of the moment of inertia and mass
		// this will tell us how much the contact point velocity will change with the forces applied

		float eMass = 1.f / (1.f / a_rigidbody->GetMass() + (r * r) / a_rigidbody->GetMoment());

		float j = -(1 + e) * velocityIntoPlane * eMass;

		glm::vec2 force = m_normal * j;

		a_rigidbody->ApplyForce(force, a_contact - a_rigidbody->GetPosition());

		float pen = glm::dot(a_contact, m_normal) - m_distanceToOrigin;

		PhysicsScene::ApplyContactForces(a_rigidbody, nullptr, m_normal, pen);
	}
	
}
