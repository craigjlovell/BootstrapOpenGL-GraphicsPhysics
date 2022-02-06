#include "AIE_PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include "Circle.h"
#include "Plane.h"

#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#define _use_math_defines
#include <math.h>

AIE_PhysicsApp::AIE_PhysicsApp() 
{
}

AIE_PhysicsApp::~AIE_PhysicsApp()
{

}

bool AIE_PhysicsApp::startup() 
{
	//timer = 30;
	// increase 2d line count to increase amount we can draw
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_physicsScene = new PhysicsScene();

	// the lower the value tge mroe accurate the simulation will be,
	// bit will increase processing time required 
	// if its to high will cause the sim to shutter and reduce the stability
	m_physicsScene->SetGravity(glm::vec2(0, 0));
	m_physicsScene->SetTimeStep(0.1f);
	
	//CreateRocket();
	CreateCircle();
	//CreatePlane();
	//CollisionDetectionTest();

	return true;
}

void AIE_PhysicsApp::shutdown() {

	delete m_font;
	delete m_2dRenderer;
}

void AIE_PhysicsApp::update(float deltaTime) {

	// input example
	aie::Input* input = aie::Input::getInstance();
	

	aie::Gizmos::clear();

	m_physicsScene->Update(deltaTime);
	m_physicsScene->Draw();

	//timer += deltaTime;
	//std::cout << "timer" << timer << std::endl;
	//if (timer > 0.2 && m_rocket->GetMass() > 1.f)
	//{
	//	m_rocket->SetMass(m_rocket->GetMass() - 1.f);
	//	UpdateRocket();
	//	timer = 0;
	//}


	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
}

void AIE_PhysicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();

	// draw your stuff here!
	static float aspectRatio = 16.f / 9.f;
	aie::Gizmos::draw2D(glm::ortho<float>(-100, 100,
		-100/aspectRatio, 100/aspectRatio, -1.f, 1.f));

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);

	// done drawing sprites
	m_2dRenderer->end();
}

void AIE_PhysicsApp::CreateCircle()
{
	Circle* ball1 = new Circle(glm::vec2(-20, 0), glm::vec2(0, 0), 1.70f, 4.f, glm::vec4(1, 1, 0, 1));
	Circle* ball2 = new Circle(glm::vec2(10, 0), glm::vec2(0, 0), 1.60f, 4.f, glm::vec4(0, 1, 0, 1));
	
	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);

	ball1->ApplyForce(glm::vec2(22.22f, -20), ball1->GetPosition());
	ball2->ApplyForce(glm::vec2(-22.22f, -20), ball2->GetPosition());

	Plane* plane = new Plane(glm::vec2(0,1), - 30);
	m_physicsScene->AddActor(plane);
	
}

void AIE_PhysicsApp::CreatePlane()
{
	Plane* testPlane = new Plane(glm::vec2(0, 1), -50);
	Plane* testPlane2 = new Plane(glm::vec2(1, 0), -40);
	Plane* testPlane3 = new Plane(glm::vec2(1, 0), +40);
	Plane* testPlane4 = new Plane(glm::vec2(-1, 1), -40);
	Plane* testPlane5 = new Plane(glm::vec2(1, 1), -40);

	m_physicsScene->AddActor(testPlane);
	m_physicsScene->AddActor(testPlane2);
	m_physicsScene->AddActor(testPlane3);
	m_physicsScene->AddActor(testPlane4);
	m_physicsScene->AddActor(testPlane5);
}

void AIE_PhysicsApp::UpdateRocket()
{
	//Circle* gas = new Circle(glm::vec2(0, -10), glm::vec2(0, 0), 0.5f, 0.5f, glm::vec4(0, 1, 0, 1));	
	//m_physicsScene->AddActor(gas);
	//m_rocket->ApplyForceToActor(gas, glm::vec2(0, -10), gas->GetPosition());
}

void AIE_PhysicsApp::CreateRocket()
{
	//m_rocket = new Circle(glm::vec2(0, 0), glm::vec2(0, 0), 30.f, 4.f, glm::vec4(0, 0, 1, 1));
	//m_physicsScene->AddActor(m_rocket);
}

void AIE_PhysicsApp::CollisionDetectionTest()
{
	Circle* ball1 = new Circle(glm::vec2(- 20, 0), glm::vec2(0, 0), 4.f, 4.f, glm::vec4(1, 0, 0, 1));
	Circle* ball2 = new Circle(glm::vec2(10, 0), glm::vec2(0, 0), 4.f, 4.f, glm::vec4(0, 1, 0, 1));
	Plane* plane = new Plane(glm::vec2(0, 1), -30);

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);
	m_physicsScene->AddActor(plane);
}
