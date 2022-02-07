#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Input.h>

#include "PhysicsObject.h"
#include "PhysicsScene.h"

class Circle;
class Plane;
class Player;

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
	void CreateCircle();
	void CreatePlane();	
	void CreateRocket();

	Player* CreatePlayer(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour);

	void UpdatePlayer(Player* a_player, aie::Input* a_input);

	void UpdateRocket();

	//====================================
};