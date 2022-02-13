#pragma once

#include "Application.h"
#include "Renderer2D.h"
#include <Input.h>

#include "PhysicsScene.h"
#include "Rigidbody.h"

class Circle;
class Plane;
class Player;
class Box;

class GameStateManager;

class AIE_PhysicsApp : public aie::Application {
public:

	AIE_PhysicsApp();
	virtual ~AIE_PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

	GameStateManager* GetGameStateManager()
	{
		return m_gameStateManager;
	}

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;
	//Circle*				m_rocket;

	PhysicsScene* m_physicsScene;

	Player* m_player;

	float timer;

	const float m_extents = 100;
	const float m_aspectRatio = 16.f / 9.f;

public:

	//====================================
	

	Plane* CreatePlane(glm::vec2 a_normal, float a_distToOrigin, glm::vec4 a_colour);
	Circle* CreateCircle(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force);
	Box* CreateBox(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);
	Player* CreatePlayer(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour);
	Player* CreatePlayer(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);

	void CreateBeacor();
	void RotstionTest();
	void Bounce();
	void CreateRocket();
	void UpdateRocket();
	void CreateAll();

	void MouseInputTest(aie::Input* a_input);
	bool m_ketPressed = false;

	void ObjectTest();

	//====================================

private:
	GameStateManager* m_gameStateManager = nullptr;
};