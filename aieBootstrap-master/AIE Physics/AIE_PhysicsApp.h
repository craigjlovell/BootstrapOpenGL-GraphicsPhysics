#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include "PhysicsObject.h"
#include "PhysicsScene.h"
#include "Circle.h"

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
	Circle*				m_rocket;

	PhysicsScene* m_physicsScene;


	float timer;

public:

	//====================================
	void CreateCircle();
	void CreatePlane();	
	void CreateRocket();

	void UpdateRocket();

	void CollisionDetectionTest();
	//====================================
};