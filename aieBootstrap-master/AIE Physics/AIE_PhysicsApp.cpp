#include "App.h"
#include "AIE_PhysicsApp.h"

#include "PhysicsScene.h"
#include "Circle.h"
#include "Plane.h"
#include "Player.h"
#include "Box.h"

#include <Gizmos.h>

#define _USE_MATH_DEFINES
#include <math.h>


AIE_PhysicsApp::AIE_PhysicsApp()
{

}

AIE_PhysicsApp::~AIE_PhysicsApp()
{

}

bool AIE_PhysicsApp::startup(App* a_app) 
{
	m_app = a_app;
	// increase 2d line count to increase amount we can draw
	
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	// TODO: remember to change this when redistributing a build!
	// the following path would be used instead: "./font/consolas.ttf"
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);


	m_physicsScene = new PhysicsScene();

	m_physicsScene->SetGravity(glm::vec2(0, 0));
	m_physicsScene->SetTimeStep(0.01f);
	
	// the lower the value tge mroe accurate the simulation will be,
	// bit will increase processing time required 
	// if its to high will cause the sim to shutter and reduce the stability
	
	
	
	CreateAll();

	return true;
}

void AIE_PhysicsApp::shutdown() 
{

	delete m_font;
	delete m_2dRenderer;
	
}

void AIE_PhysicsApp::update(float deltaTime) 
{

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

	MouseInputTest(input);
}

void AIE_PhysicsApp::draw() 
{

}

glm::vec2 AIE_PhysicsApp::ScreenToWorld(glm::vec2 a_screenPos)
{
	glm::vec2 worldPos = a_screenPos;
	
	//move the centre of the screen to (0,0)
	worldPos.x -= m_app->getWindowWidth() / 2;
	worldPos.y -= m_app->getWindowHeight() / 2;

	worldPos.x *= 2.f * m_extents / m_app->getWindowWidth();
	worldPos.y *= 2.f * m_extents / (m_aspectRatio * m_app->getWindowHeight());

	return worldPos;
}

void AIE_PhysicsApp::CreateAll()
{
	m_player = CreatePlayer(glm::vec2(-40, 0), glm::vec2(0, 0), 4.f, 4.f, glm::vec4(.5f, .5f, .5f, 1.f));
	//m_player = CreatePlayer(glm::vec2(0, 40), glm::vec2(0, 0), 1, 4, 8, 4, glm::vec4(1, 1, 1, 1));

	//Box* box1 = CreateBox(glm::vec2(20, 0), glm::vec2(0, 0), 0, 4, 8, 4, glm::vec4(1, 0, 1, 1));
	//Box* box2 = CreateBox(glm::vec2(20, 20), glm::vec2(0, 0), 0, 4, 8, 4, glm::vec4(1, 1, 1, 1));
	
	//Circle* ball1 = CreateCircle(glm::vec2(20, 30), glm::vec2(0, 0), 4, 4, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	//Circle* ball2 = CreateCircle(glm::vec2(20, 40), glm::vec2(0, 0), 4, 4, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));

	//Plane* plane = new Plane(glm::vec2(0, 1), -30);
	//m_physicsScene->AddActor(plane);


	//CreateRocket();
	//CreateCircle();
	//CreatePlane();
	//RotstionTest();
	//CollisionDetectionTest();
	//ObjectTest();
	Pool();
	//Bounce();
}

void AIE_PhysicsApp::MouseInputTest(aie::Input* a_input)
{
	int xScreen, yScreen;
	if (a_input->isMouseButtonDown(0))
	{
		m_ketPressed = true;		
		a_input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		aie::Gizmos::add2DCircle(worldPos, 5, 32, glm::vec4(0.1f, 0.1f, 0.9f, 1.f));
	}
	if (a_input->wasMouseButtonReleased(0))
	{
		a_input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		Circle* spawn = new Circle(worldPos, glm::vec2(0), 4.f, 4.f, glm::vec4(0.1f, 0.1f, 0.4f, 1.f));
		m_physicsScene->AddActor(spawn);
	}
}

void AIE_PhysicsApp::Pool()
{
	Circle* middleTopHole = CreateCircle(glm::vec2(0, 30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0,0));
	middleTopHole->SetKinematic(true);
	middleTopHole->SetTrigger(true);

	Circle* rightTopHole = CreateCircle(glm::vec2(50, 30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	rightTopHole->SetKinematic(true);
	rightTopHole->SetTrigger(true);

	Circle* leftTopHole = CreateCircle(glm::vec2(-50, 30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	leftTopHole->SetKinematic(true);
	leftTopHole->SetTrigger(true);

	Circle* middleBottomHole = CreateCircle(glm::vec2(0, -30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	middleBottomHole->SetKinematic(true);
	middleBottomHole->SetTrigger(true);

	Circle* rightBottomHole = CreateCircle(glm::vec2(50, -30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	rightBottomHole->SetKinematic(true);
	rightBottomHole->SetTrigger(true);

	Circle* leftBottomHole = CreateCircle(glm::vec2(-50, -30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	leftBottomHole->SetKinematic(true);
	leftBottomHole->SetTrigger(true);

	middleBottomHole->triggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};

	Circle* ball1 = new Circle(glm::vec2(40, 0), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 1.f, 0.f, 1.f));
	m_physicsScene->AddActor(ball1);

	m_physicsScene->AddActor(new Circle(glm::vec2(40, 2.5), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(40, -2.5), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(40, -5), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 1.f, 0.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(40, 5), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 1.f, 0.f, 1.f)));

	m_physicsScene->AddActor(new Circle(glm::vec2(36, -6), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(36, 6), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 1.f, 0.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(36, 3), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(36, -3), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 1.f, 0.f, 1.f)));

	m_physicsScene->AddActor(new Circle(glm::vec2(32, 0), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 1.f, 0.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(32, 1), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(32, -1), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1.f, 1.f, 1.f, 1.f)));

	m_physicsScene->AddActor(new Circle(glm::vec2(28, -2), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f)));
	m_physicsScene->AddActor(new Circle(glm::vec2(28, 2), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 1.f, 0.f, 1.f)));

	m_physicsScene->AddActor(new Circle(glm::vec2(24, 0), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(0.f, 0.f, 1.f, 1.f)));

	Box* topleft = new Box(glm::vec2(-25, 35), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(1.f,1.f,1.f,1.f));
	m_physicsScene->AddActor(topleft);
	topleft->SetKinematic(true);
	Box* topright = new Box(glm::vec2(25, 35), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(1.f, 1.f, 1.f, 1.f));
	m_physicsScene->AddActor(topright);
	topright->SetKinematic(true);
	Box* top = new Box(glm::vec2(0, 40), glm::vec2(0, 0), 0, 4.f, 125.f, 4.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(top);
	top->SetKinematic(true);

	Box* bottomleft = new Box(glm::vec2(-25, -35), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(1.f, 1.f, 1.f, 1.f));
	m_physicsScene->AddActor(bottomleft);
	bottomleft->SetKinematic(true);
	Box* bottomright = new Box(glm::vec2(25, -35), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(1.f, 1.f, 1.f, 1.f));
	m_physicsScene->AddActor(bottomright);
	bottomright->SetKinematic(true);
	Box* bottom = new Box(glm::vec2(0, -40), glm::vec2(0, 0), 0, 4.f, 125.f, 4.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(bottom);
	bottom->SetKinematic(true);

	Box* left = new Box(glm::vec2(-55, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 55.f, glm::vec4(1.f, 1.f, 1.f, 1.f));
	m_physicsScene->AddActor(left);
	left->SetKinematic(true);
	Box* oleft = new Box(glm::vec2(-65, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 85.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(oleft);
	oleft->SetKinematic(true);

	Box* right = new Box(glm::vec2(55, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 55.f, glm::vec4(1.f, 1.f, 1.f, 1.f));
	m_physicsScene->AddActor(right);
	right->SetKinematic(true);
	Box* oright = new Box(glm::vec2(65, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 85.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(oright);
	oright->SetKinematic(true);
	
}

void AIE_PhysicsApp::ObjectTest()
{
	m_physicsScene->SetGravity(glm::vec2(0, -9.82f));
	Circle* ball1 = new Circle(glm::vec2(10, 0), glm::vec2(0, 0), 4.f, 4.f, glm::vec4(0, 1, 0, 1));
	Circle* ball2 = new Circle(glm::vec2(10, -20), glm::vec2(0, 0), 4.f, 4.f, glm::vec4(1, 0, 0, 1));
	ball2->SetKinematic(true);
	ball2->SetTrigger(true);

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);

	m_physicsScene->AddActor(new Plane(glm::vec2(1, 0), -30));
	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -50));
	m_physicsScene->AddActor(new Plane(glm::vec2(-1, 0), -50));

	ball2->triggerEnter = [=](PhysicsObject* a_other)
	{
		std::cout << "Entered:" << a_other << std::endl;
	};
	ball2->triggerExit = [=](PhysicsObject* a_other)
	{
		std::cout << "Exited:" << a_other << std::endl;
	};

}

void AIE_PhysicsApp::RotstionTest()
{
	//Circle* ball1 = new Circle(glm::vec2(20, 20), glm::vec2(0, 0), 1.70f, 4.f, glm::vec4(0.1, 0, 0.3, 1));
	//m_physicsScene->AddActor(ball1);
	//ball1->ApplyForce(glm::vec2(0.f, -20.f), ball1->GetPosition());

	Box* box1 = new Box(glm::vec2(20, 0), glm::vec2(0, 0), 0, 4, 8, 4);
	m_physicsScene->AddActor(box1);
	box1->ApplyForce(glm::vec2(0.f, -20.f), box1->GetPosition());

	Box* box2 = new Box(glm::vec2(20, 20), glm::vec2(0, 0), 0, 4, 8, 4);
	m_physicsScene->AddActor(box2);
	box2->ApplyForce(glm::vec2(0.f, -20.f), box2->GetPosition());

	Plane* plane = new Plane(glm::vec2(0, 1), -30);
	m_physicsScene->AddActor(plane);
}

void AIE_PhysicsApp::Bounce()
{
	Circle* ball1 = new Circle(glm::vec2(-20, 0), glm::vec2(0, 0), 1.70f, 4.f, glm::vec4(1, 1, 0, 1));
	Circle* ball2 = new Circle(glm::vec2(10, 0), glm::vec2(0, 0), 1.60f, 4.f, glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(ball1);
	m_physicsScene->AddActor(ball2);

	ball1->ApplyForce(glm::vec2(22.22f, -20), ball1->GetPosition());
	ball2->ApplyForce(glm::vec2(-22.22f, -20), ball2->GetPosition());


	Plane* plane = new Plane(glm::vec2(0, 1), -30);
	m_physicsScene->AddActor(plane);
}

void AIE_PhysicsApp::CreateBeacor()
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

Plane* AIE_PhysicsApp::CreatePlane(glm::vec2 a_normal, float a_distToOrigin, glm::vec4 a_colour)
{
	Plane* plane = new Plane(a_normal, a_distToOrigin, a_colour);

	m_physicsScene->AddActor(plane);

	return plane;
}

Player* AIE_PhysicsApp::CreatePlayer(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour) // Circle
{
	Player* player = new Player(a_pos, a_vel, a_mass, a_radius, a_colour);

	m_physicsScene->AddActor(player);

	return player;
}

Player* AIE_PhysicsApp::CreatePlayer(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour) // Box
{
	Player* player = new Player(a_position, a_velocity, a_rotation, a_mass, a_width, a_height, a_colour);

	m_physicsScene->AddActor(player);

	return player;
}

Circle* AIE_PhysicsApp::CreateCircle(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force)
{
	Circle* circle = new Circle(a_pos, a_vel, a_mass, a_radius, a_colour);

	m_physicsScene->AddActor(circle);

	circle->ApplyForce(a_force, circle->GetPosition());

	return circle;
}

Box* AIE_PhysicsApp::CreateBox(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour)
{
	Box* box = new Box(a_position, a_velocity, a_rotation, a_mass, a_width, a_height, a_colour);

	m_physicsScene->AddActor(box);

	//box->ApplyForce(glm::vec2(0.f, -20.f), box->GetPosition());

	return box;
}



