#include "Box.h"
#include "Rigidbody.h"
#include <Gizmos.h>

Box::Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height) :
	Rigidbody(BOX, a_position, a_velocity, a_rotation, a_mass)
{
	m_extents = glm::vec2(a_width / 2, a_height / 2);
	m_colour = glm::vec4(0, 0, 1, 1);
	m_moment = 1.f / 12.f * a_mass * a_width * a_height;
}

Box::Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour) :
	Rigidbody(BOX, a_position, a_velocity, a_rotation, a_mass)
{
	m_extents = glm::vec2(a_width / 2, a_height / 2);
	m_colour = a_colour;
	m_moment = 1.f / 12.f * a_mass * a_width * a_height;
}

Box::Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, glm::vec2 a_dimensions) :
	Rigidbody(BOX, a_position, a_velocity, a_rotation, a_mass)
{
	m_extents = glm::vec2(a_dimensions.x / 2, a_dimensions.y / 2);
	m_colour = glm::vec4(0, 0, 1, 1);
	m_moment = 1.f / 12.f * a_mass * a_dimensions.x * a_dimensions.y;
}

Box::Box(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, glm::vec2 a_dimensions, glm::vec4 a_colour) :
	Rigidbody(BOX, a_position, a_velocity, a_rotation, a_mass)
{
	m_extents = glm::vec2(a_dimensions.x / 2, a_dimensions.y / 2);
	m_colour = a_colour;
	m_moment = 1.f / 12.f * a_mass * a_dimensions.x * a_dimensions.y;
}

Box::~Box()
{

}

void Box::FixedUpdate(glm::vec2 a_gravity, float a_timestep)
{
	Rigidbody::FixedUpdate(a_gravity, a_timestep);

	// first store the local axes
	float cs = cosf(m_rotation);
	float sn = sinf(m_rotation);
	m_localX = glm::normalize(glm::vec2(cs, sn));
	m_localY = glm::normalize(glm::vec2(-sn, cs));
}

void Box::MakeGizmo()
{
	// drawing using our local axes
	glm::vec2 p1 = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p2 = m_position + m_localX * m_extents.x - m_localY * m_extents.y;
	glm::vec2 p3 = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
	glm::vec2 p4 = m_position + m_localX * m_extents.x + m_localY * m_extents.y;

	aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
	aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
}

bool Box::CheckBoxCorners(const Box& a_box, glm::vec2& a_contact, int& a_numContact, float& a_pen, glm::vec2& a_edgeNormal)
{
	float minX, maxX, minY, maxY;
	float boxW = a_box.m_extents.x * 2;
	float boxH = a_box.m_extents.y * 2;
	int numLocalContacts = 0;
	glm::vec2 localContact(0, 0);
	bool first = true;

	// loop over all corners of the other box
	for (float x = -a_box.m_extents.x; x < boxW; x += boxW)
	{
		for (float y = -a_box.m_extents.y; y < boxH; y += boxH)
		{
			// get pos in worldspace
			glm::vec2 p = a_box.m_position + x * a_box.m_localX + y * a_box.m_localY;
			//get pos in our box space
			glm::vec2 p0(glm::dot(p - m_position, m_localX), glm::dot(p - m_position, m_localY));

			// update the extents in each cardinal direction in our box space
			//(ie extents along the seprating axes)
			if (first || p0.x < minX) minX = p0.x;
			if (first || p0.x > maxX) maxX = p0.x;
			if (first || p0.y < minY) minY = p0.y;
			if (first || p0.y > maxY) maxY = p0.y;

			//if this corner is inside the box, add it to the list of contact points
			if (p0.x >= -m_extents.x && p0.x <= m_extents.x &&
				p0.y >= -m_extents.y && p0.y <= m_extents.y)
			{
				numLocalContacts++;
				localContact += p0;
			}
			first = false;
		}
	}

	// if we lie entirely to one side of the box along one axis, we've found a seprating axes amd we cam exit
	if(maxX <= -m_extents.x || minX >= m_extents.x ||
		maxY <= -m_extents.y || minY >= m_extents.y)
		return false;

	if (numLocalContacts == 0)
		return false;

	bool res = false;
	a_contact += m_position + (localContact.x * m_localX + localContact.y * m_localY) / (float)numLocalContacts;
	a_numContact++;

	// find the minimum penetration vector as a penetration amount and normal
	float pen0 = m_extents.x - minX;
	if (pen0 > 0 && (pen0 < a_pen || a_pen == 0))
	{
		a_edgeNormal = m_localX;
		a_pen = pen0;
		res = true;
	}
	pen0 = maxX + m_extents.x;
	if (pen0 > 0 && (pen0 < a_pen || a_pen == 0))
	{
		a_edgeNormal = -m_localX;
		a_pen = pen0;
		res = true;
	}
	pen0 = m_extents.y - minY;
	if (pen0 > 0 && (pen0 < a_pen || a_pen == 0))
	{
		a_edgeNormal = m_localY;
		a_pen = pen0;
		res = true;
	}
	pen0 = maxY + m_extents.y;
	if (pen0 > 0 && (pen0 < a_pen || a_pen == 0))
	{
		a_edgeNormal = -m_localY;
		a_pen = pen0;
		res = true;
	}
	return res;
}

