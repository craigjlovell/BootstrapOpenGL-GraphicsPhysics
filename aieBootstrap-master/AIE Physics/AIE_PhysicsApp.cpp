#include "AIE_PhysicsApp.h"
#include "Texture.h"
#include "Font.h"
#include "Input.h"
#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>


AIE_PhysicsApp::AIE_PhysicsApp() {

}

AIE_PhysicsApp::~AIE_PhysicsApp() {

}

bool AIE_PhysicsApp::startup() {

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
	m_physicsScene->SetTimeStep(0.01f);

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

	
	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);

	// done drawing sprites
	m_2dRenderer->end();
}