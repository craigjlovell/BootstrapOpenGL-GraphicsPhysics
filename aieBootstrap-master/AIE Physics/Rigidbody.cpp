#include "Rigidbody.h"
#include <glm/glm.hpp>
#include <Gizmos.h>
#include <glm/ext.hpp>
#include <iostream>
#include <math.h>

#include <string>
#include <stdio.h>
#include <ctype.h>

#define MIN_LINEAR_THRESHOLD 0
#define MIN_ANGULAR_THRESHOLD 0

Rigidbody::Rigidbody(ShapeType a_shapeID, glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass) : PhysicsObject(a_shapeID)
{
	m_position = a_position;
	m_velocity = a_velocity;
	m_rotation = a_rotation;
	m_mass = a_mass;
	m_elasticity = 1;
	m_angularVelocity = 0;
}

Rigidbody::~Rigidbody()
{

}

void Rigidbody::FixedUpdate(glm::vec2 a_gravity, float a_timeStep)
{
	m_position += GetVelocity() * a_timeStep;
	ApplyForce(a_gravity * GetMass() * a_timeStep, glm::vec2(0, 0));

	m_rotation += m_angularVelocity * a_timeStep;

    m_velocity -= m_velocity * m_linearDrag * a_timeStep;
    m_angularVelocity -= m_angularVelocity * m_angularDrag * a_timeStep;

    if (length(m_velocity) < MIN_LINEAR_THRESHOLD)
    {
        m_velocity = glm::vec2(0, 0);
    }
    if (abs(m_angularVelocity) < MIN_ANGULAR_THRESHOLD)
    {
        m_angularVelocity = 0;
    }
}

void Rigidbody::ResolveCollision(Rigidbody* a_otherActor, glm::vec2 a_contact,
    glm::vec2* a_collisionNormal, float pen)
{
    // We need to find the vector betweem their centers or use the 
    // provided directional force, and make sure it is normalised
    glm::vec2 normal = glm::normalize(a_collisionNormal ? *a_collisionNormal : a_otherActor->GetPosition() - m_position);

    //Get the perpendicular vector to the collision normal
    glm::vec2 perpendicularColNorm(normal.y, -normal.x);
    float radiusThis = glm::dot(a_contact - m_position, -perpendicularColNorm);
    float radiusOther = glm::dot(a_contact - a_otherActor->GetPosition(), perpendicularColNorm);

    // the velocity of the contact points
    float cp_velocityThis = glm::dot(m_velocity, normal) - radiusThis * m_angularVelocity;
    float cp_velocityOther = glm::dot(a_otherActor->GetVelocity(), normal) + radiusOther * a_otherActor->GetAngularVelocity();

    // they are moving closer
    if (cp_velocityThis > cp_velocityOther) 
    {
        // This will caculate the effective mass at the contact point for each object
        // ie. how much the contact point will move due to the force applied
        float massThis = 1.f / (1.f / m_mass + glm::pow(radiusThis, 2.f) / m_moment);
        float massOther = 1.f / (1.f / a_otherActor->GetMass() + glm::pow(radiusOther, 2.f) / a_otherActor->GetMoment());
        float elasticity = (m_elasticity + a_otherActor->GetElasticity()) / 2.f;
        glm::vec2 impact = (1.f + elasticity) * massThis * massOther / (massThis + massOther) * (cp_velocityThis - cp_velocityOther) * normal;
        ApplyForce(-impact, a_contact - m_position);
        a_otherActor->ApplyForce(impact, a_contact - a_otherActor->GetPosition());
    }
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
	//float totalEnergy = (m_mass * glm::dot(m_velocity, m_velocity)) / 2;
	//return totalEnergy;

    return 0.5f * (m_mass * glm::dot(m_velocity, m_velocity) + m_moment * m_angularVelocity * m_angularVelocity);
}

float Rigidbody::ColourChange(float a_colour)
{
    // converting percentile to rgb
    int rgb = glm::round(a_colour * 255);
    
    // converting rbg to hex
    float hexValue = rgb / 16;
    int hex1 = glm::round(hexValue);
    int hex2 = (hexValue - hex1) * 16;

    // flipping hex
    hex1 = 15 - hex1;
    hex2 = 15 - hex2;

    // converting hex back to rgb
    rgb = (hex1 * 16) + hex2;

    // converting back to percentile 
    float percentile = rgb / 255;

    return percentile;
}
