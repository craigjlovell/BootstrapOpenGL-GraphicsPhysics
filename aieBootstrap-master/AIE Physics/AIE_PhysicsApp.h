#pragma once

#include "App.h"
#include "Renderer2D.h"
#include <Input.h>

#include "PhysicsScene.h"
#include "GameStateManager.h"

class Circle;
class Plane;
class Player;
class Box;
class App;

class AIE_PhysicsApp
{
public:

	AIE_PhysicsApp();
	virtual ~AIE_PhysicsApp();

	virtual bool startup(App* a_app);
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

	

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	App* m_app;
	PhysicsScene* m_physicsScene;

	Player* m_player;
	Circle* m_circle;

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
	void Pool();
	bool m_ketPressed = false;

	void ObjectTest();

	//====================================

private:
};