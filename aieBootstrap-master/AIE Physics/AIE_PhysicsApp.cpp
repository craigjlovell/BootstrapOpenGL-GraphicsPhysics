#include "App.h"
#include "AIE_PhysicsApp.h"

#include "PhysicsScene.h"
#include "Circle.h"
#include "Plane.h"
#include "Player.h"
#include "Box.h"
#include "Spring.h"
#include "Softbody.h"
#include "Ball.h"

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
	//m_player = CreatePlayer(glm::vec2(-40, 0), glm::vec2(0, 0), 4.f, 4.f, glm::vec4(.5f, .5f, .5f, 1.f));
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
	//SpringTest(10);
	//SoftBodyTest();

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
		aie::Gizmos::add2DLine(worldPos, m_white->GetPosition(), glm::vec4(1,1,1,1));
	}
	if (a_input->wasMouseButtonReleased(0))
	{
		a_input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		m_white->ApplyForce(-worldPos, glm::vec2(0, 0));
	}
}

void AIE_PhysicsApp::Pool()
{
	int numRed = 7;
	int numYellow = 7;
	int num = 14;

	Box* table = new Box(glm::vec2(0, 0), glm::vec2(0, 0), 0, 4.f, 102.5f, 55.5f, glm::vec4(0.f, 0.5f, 0.f, 1.f));
	m_physicsScene->AddActor(table);
	table->SetKinematic(true);
	table->SetTrigger(true);

	Box* topleft = new Box(glm::vec2(-25, 30), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(.5f, .3f, .04f, 1));
	m_physicsScene->AddActor(topleft);
	topleft->SetKinematic(true);
	Box* topright = new Box(glm::vec2(25, 30), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(.5f, .3f, .04f, 1));
	m_physicsScene->AddActor(topright);
	topright->SetKinematic(true);
	Box* top = new Box(glm::vec2(0, 40), glm::vec2(0, 0), 0, 4.f, 125.f, 4.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(top);
	top->SetKinematic(true);

	Box* bottomleft = new Box(glm::vec2(-25, -30), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(.5f, .3f, .04f, 1));
	m_physicsScene->AddActor(bottomleft);
	bottomleft->SetKinematic(true);
	Box* bottomright = new Box(glm::vec2(25, -30), glm::vec2(0, 0), 0, 4.f, 42.5f, 4.f, glm::vec4(.5f, .3f, .04f, 1));
	m_physicsScene->AddActor(bottomright);
	bottomright->SetKinematic(true);
	Box* bottom = new Box(glm::vec2(0, -40), glm::vec2(0, 0), 0, 4.f, 125.f, 4.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(bottom);
	bottom->SetKinematic(true);

	Box* left = new Box(glm::vec2(-52.5f, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 50.f, glm::vec4(.5f, .3f, .04f, 1));
	m_physicsScene->AddActor(left);
	left->SetKinematic(true);
	Box* oleft = new Box(glm::vec2(-65, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 85.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(oleft);
	oleft->SetKinematic(true);

	Box* right = new Box(glm::vec2(52.5f, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 50.f, glm::vec4(.5f, .3f, .04f, 1));
	m_physicsScene->AddActor(right);
	right->SetKinematic(true);
	Box* oright = new Box(glm::vec2(65, 0), glm::vec2(0, 0), 0, 4.f, 4.f, 85.f, glm::vec4(1.f, 0.8f, 0.5f, 1.f));
	m_physicsScene->AddActor(oright);
	oright->SetKinematic(true);

	

	Circle* middleTopHole = CreateCircle(glm::vec2(0, 30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0,0));
	middleTopHole->SetKinematic(true);
	middleTopHole->SetTrigger(true);

	Circle* rightTopHole = CreateCircle(glm::vec2(50, 27.5f), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	rightTopHole->SetKinematic(true);
	rightTopHole->SetTrigger(true);

	Circle* leftTopHole = CreateCircle(glm::vec2(-50, 27.5f), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	leftTopHole->SetKinematic(true);
	leftTopHole->SetTrigger(true);

	Circle* middleBottomHole = CreateCircle(glm::vec2(0, -30), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	middleBottomHole->SetKinematic(true);
	middleBottomHole->SetTrigger(true);

	Circle* rightBottomHole = CreateCircle(glm::vec2(50, -27.5f), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	rightBottomHole->SetKinematic(true);
	rightBottomHole->SetTrigger(true);

	Circle* leftBottomHole = CreateCircle(glm::vec2(-50, -27.5f), glm::vec2(0, 0), 4.f, 2.f, glm::vec4(1, 0, 0, 1), glm::vec2(0, 0));
	leftBottomHole->SetKinematic(true);
	leftBottomHole->SetTrigger(true);

	m_white = CreateBall(glm::vec2(-40, 0), glm::vec2(0, 0), 1.5f, 2.f, glm::vec4(1,1,1,1), glm::vec2(0,0), WHITEBALL);
	

	Circle* circle = nullptr;

	float circleRadius = 2.f;

	float xStart = 40.f; // 40;
	float yStart = 10.f; // 5;

	float xOffset = 5.f; // 3;
	float yOffset = 5.f; // 5;

	glm::vec4 yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 red = glm::vec4(1, 0, 0, 1);
	glm::vec4 black = glm::vec4(0, 0, 0, 1);
	glm::vec4 colour;
	BallType typeOfBall;

	
	for (int x = 0; x < 5; x++)
	{
		for (int y = 0; y < 5 - x; y++)
		{
			float xPos = xStart - (xOffset * x);
			float yPos = 1 + yStart - (yOffset / 2 * x) - (2 / circleRadius + yOffset * y);

			glm::vec2 pos = glm::vec2(xPos, yPos);			

			if (x == 0)
				if (y == 0 || y == 1 || y == 3)
				{
					colour = yellow;
					typeOfBall = SOLID;
				}
				else
				{
					colour = red;
					typeOfBall = STRIPE;
				}
			if (x == 1)
				if (y == 1 || y == 3)
				{
					colour = yellow;
					typeOfBall = SOLID;
				}
				else
				{
					colour = red;
					typeOfBall = STRIPE;
				}
			if (x == 2)
				if (y == 0)
				{
					colour = yellow;
					typeOfBall = SOLID;
				}
				else if (y == 1)
				{
					colour = black;
					typeOfBall = BLACKBALL;
				}
				else
				{
					colour = red;
					typeOfBall = STRIPE;
				}
			if (x == 3)
				if (y == 1)
				{
					colour = yellow;
					typeOfBall = SOLID;
				}
				else
				{
					colour = red;
					typeOfBall = STRIPE;
				}
			else if (x == 4)
			{
				colour = red;
				typeOfBall = STRIPE;
			}
			CreateBall(pos, glm::vec2(0), 1.f, circleRadius, colour, glm::vec2(0, 0), typeOfBall);
		}
	}

	middleTopHole->triggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};
	rightTopHole->triggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};
	leftTopHole->triggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};
	middleBottomHole->triggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};
	rightBottomHole->triggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};
	leftBottomHole->triggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};	
	
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

void AIE_PhysicsApp::SoftBodyTest()
{
	std::vector<std::string> c;
	std::vector<std::string> r;
	std::vector<std::string> a;
	std::vector<std::string> i;
	std::vector<std::string> g;
	c.push_back("000000");  r.push_back("00...."); a.push_back("....00"); i.push_back("00"); g.push_back("000000");
	c.push_back("000000"); 	r.push_back("00...."); a.push_back("000000"); i.push_back("00"); g.push_back("....00");
	c.push_back("00...."); 	r.push_back("00...."); a.push_back("000000"); i.push_back("00"); g.push_back("000000");
	c.push_back("00...."); 	r.push_back("00...0"); a.push_back("00..00"); i.push_back("00"); g.push_back("000000");
	c.push_back("000000"); 	r.push_back("000000"); a.push_back("000000"); i.push_back(".."); g.push_back("00..00");
	c.push_back("000000"); 	r.push_back("000000"); a.push_back("000000"); i.push_back("00"); g.push_back("000000");

	Softbody::Build(m_physicsScene, glm::vec2(-80, 0), 5.0f, 2000.f, 1.f, c);
	Softbody::Build(m_physicsScene, glm::vec2(-45, 0), 5.0f, 2000.f, 1.f, r);
	Softbody::Build(m_physicsScene, glm::vec2(-10, 0), 5.0f, 2000.f, 1.f, a);
	Softbody::Build(m_physicsScene, glm::vec2(25, 0), 5.0f, 2000.f, 1.f, i);
	Softbody::Build(m_physicsScene, glm::vec2(40, 0), 5.0f, 2000.f, 1.f, g);
	m_physicsScene->AddActor(new Plane(glm::vec2(0, 1), -30));
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

void AIE_PhysicsApp::SpringTest(int a_amount)
{
	Circle* prev = nullptr;
	for (int i = 0; i < a_amount; i++)
	{
		//Spawn a new Circle below the last.
		Circle* circle = new Circle(glm::vec2(i * 3, 30 - i * 5), glm::vec2(0), 10,2,glm::vec4(0,0,1,1));
		if (i == 0)
			circle->SetKinematic(true);
		m_physicsScene->AddActor(circle);
		if (prev)
			m_physicsScene->AddActor(new Spring(circle, prev, 10, 500));
		prev = circle;
		
	}

	Box* box = new Box(glm::vec2(0, -20), glm::vec2(0), 0.3f, 20, glm::vec2(8, 2), glm::vec4(0, 1, 1, 1));
	box->SetKinematic(true);
	m_physicsScene->AddActor(box);
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

Ball* AIE_PhysicsApp::CreateBall(glm::vec2 a_pos, glm::vec2 a_vel, float a_mass, float a_radius, glm::vec4 a_colour, glm::vec2 a_force, BallType a_balls)
{
	Ball* ball = new Ball(a_pos, a_vel, a_mass, a_radius, a_colour, a_balls);

	m_physicsScene->AddActor(ball);

	ball->ApplyForce(a_force, ball->GetPosition());

	return ball;
}

Box* AIE_PhysicsApp::CreateBox(glm::vec2 a_position, glm::vec2 a_velocity, float a_rotation, float a_mass, float a_width, float a_height, glm::vec4 a_colour)
{
	Box* box = new Box(a_position, a_velocity, a_rotation, a_mass, a_width, a_height, a_colour);

	m_physicsScene->AddActor(box);

	box->ApplyForce(glm::vec2(0.f, -20.f), box->GetPosition());

	return box;
}



