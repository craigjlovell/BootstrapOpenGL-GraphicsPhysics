#include "Player.h"
#include "Rigidbody.h"
#include <Gizmos.h>

Player::Player(glm::vec2 a_position, glm::vec2 a_velocity,
	float a_mass, float a_radius, glm::vec4 a_colour) : 
	Rigidbody(CIRCLE, a_position, a_velocity, 0, a_mass)
{
	m_radius = a_radius;
	m_colour = a_colour;
	m_isKinematic = false;
	m_moment = .5f * m_mass * a_radius * a_radius;
}

Player::Player(glm::vec2 a_position, glm::vec2 a_velocity, 
	float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour) : 
	Rigidbody(BOX, a_position, a_velocity, 0, a_mass)
{
	m_extents = glm::vec2(a_width / 2, a_height / 2);
	m_colour = a_colour;
	m_moment = 1.f / 12.f * a_mass * a_width * a_height;
}


Player::~Player()
{

}

void Player::FixedUpdate(glm::vec2 a_gravity, float a_timestep)
{
	Rigidbody::FixedUpdate(a_gravity, a_timestep);

	aie::Input* input = aie::Input::getInstance();

	if (GetShapeID() == BOX)
	{
		// first store the local axes
		float cs = cosf(m_rotation);
		float sn = sinf(m_rotation);
		m_localX = glm::normalize(glm::vec2(cs, sn));
		m_localY = glm::normalize(glm::vec2(-sn, cs));
	}
	UpdatePlayer(this, input);
}

void Player::MakeGizmo()
{

	if (GetShapeID() == BOX)
	{
		glm::vec2 p1 = m_position - m_localX * m_extents.x - m_localY * m_extents.y;
		glm::vec2 p2 = m_position + m_localX * m_extents.x - m_localY * m_extents.y;
		glm::vec2 p3 = m_position - m_localX * m_extents.x + m_localY * m_extents.y;
		glm::vec2 p4 = m_position + m_localX * m_extents.x + m_localY * m_extents.y;

		aie::Gizmos::add2DTri(p1, p2, p4, m_colour);
		aie::Gizmos::add2DTri(p1, p4, p3, m_colour);
	}
	if (GetShapeID() == CIRCLE)
	{
		aie::Gizmos::add2DCircle(m_position, m_radius, 15, m_colour);
	}
	

	
}

void Player::UpdatePlayer(Player* a_player, aie::Input* a_input)
{
	if (a_input->isKeyDown(aie::INPUT_KEY_W)) a_player->ApplyForce(glm::vec2(0, 3), a_player->GetPosition());
	if (a_input->isKeyDown(aie::INPUT_KEY_S)) a_player->ApplyForce(glm::vec2(0, -3), a_player->GetPosition());
	if (a_input->isKeyDown(aie::INPUT_KEY_A)) a_player->ApplyForce(glm::vec2(-3, 0), a_player->GetPosition());
	if (a_input->isKeyDown(aie::INPUT_KEY_D)) a_player->ApplyForce(glm::vec2(3, 0), a_player->GetPosition());
}