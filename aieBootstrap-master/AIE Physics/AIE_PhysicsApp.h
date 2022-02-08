#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Input.h>

#include "PhysicsObject.h"
#include "PhysicsScene.h"

class Circle;
class Plane;
class Player;
class Box;

class AIE_PhysicsApp : public aie::Application {
public:

	AIE_PhysicsApp();
	virtual ~AIE_PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	//Circle*				m_rocket;

	PhysicsScene* m_physicsScene;

	Player* m_player;


	float timer;

public:

	//====================================
	void RotstionTest();

	void Bounce();
	
	void CreateRocket();

	Plane* CreatePlane(glm::vec2 a_normal, float a_distToOrigin, glm::vec4 a_colour);
	Circle* CreateCircle(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force);
	Box* CreateBox(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);
	Player* CreatePlayer(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour);
	Player* CreatePlayer(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);

	void UpdatePlayer(Player* a_player, aie::Input* a_input);
	void CreateBeacor();

	void UpdateRocket();

	//====================================
};