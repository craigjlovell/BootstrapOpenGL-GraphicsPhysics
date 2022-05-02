#pragma once

#include "App.h"
#include "Renderer2D.h"
#include <Input.h>

#include "PhysicsScene.h"
#include "GameStateManager.h"

class App;
class Circle;
class Plane;
class Player;
class Box;
class Ball;


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
	Ball* m_white;
	Circle* m_hole;

	std::list<PhysicsObject*>m_stripe;
	std::list<PhysicsObject*>m_solid;

	bool m_moving = false;
	bool m_movingLastFrame = false;
	bool m_firstBallSunk = false;
	bool m_ballSunk = false;
	bool m_playersTurn = false;


	glm::vec4 c_colour;
	glm::vec4 c_yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 c_red = glm::vec4(1, 0, 0, 1);
	glm::vec4 c_black = glm::vec4(0, 0, 0, 1);
	
	BallType typeOfBall;
	float timer;

	const float m_extents = 100;
	const float m_aspectRatio = 16.f / 9.f;
	glm::vec2 m_forcestart = glm::vec2(0, 0);
	glm::vec2 m_cforce = glm::vec2(0, 0);
	std::list<Ball*> m_balls;
	bool m_ballsStatic = true;


public:

	//====================================
	

	Plane* CreatePlane(glm::vec2 a_normal, float a_distToOrigin, glm::vec4 a_colour);
	Circle* CreateCircle(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force);
	Ball* CreateBall(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force, BallType a_balls);
	Circle* CreateHole(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force);
	Box* CreateBox(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);
	Box* CreateTable(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);
	Player* CreatePlayer(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour);
	Player* CreatePlayer(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour);

	void HitCueBall(aie::Input* a_input);

	void HitCueBall2(aie::Input* a_input);

	void CreateBeacor();
	void RotstionTest();
	void Bounce();
	void CreateRocket();
	void SpringTest(int a_amount);
	void UpdateRocket();
	void CreateAll();

	void MouseInputTest(aie::Input* a_input);
	void Pool();
	bool m_ketPressed = false;

	void ObjectTest();

	void SoftBodyTest();

	//====================================

private:
};