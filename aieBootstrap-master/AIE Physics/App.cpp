#include "App.h"
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "GameStateManager.h"

#include "MenuState.h"
#include "GameState.h"

App::App() : Application()
{
}

App::~App()
{
}

bool App::startup()
{
	aie::Gizmos::create(255U, 255U, 65535U, 65535U);

	m_2dRenderer = new aie::Renderer2D();

	m_font = new aie::Font("../bin/font/consolas.ttf", 32);

	m_gameStateManager = new GameStateManager();
	m_gameStateManager->SetState("Menu", new MenuState(this));
	m_gameStateManager->SetState("Game", new GameState(this));

	m_gameStateManager->PushState("Menu");
	return true;
}

void App::shutdown()
{
	
	m_gameStateManager->shutdown();
	delete m_font;
	delete m_2dRenderer;
	delete m_gameStateManager;
}

void App::update(float deltaTime)
{
	m_gameStateManager->update(deltaTime);
	aie::Input* input = aie::Input::getInstance();

	// exit the application
	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();

	
}

void App::draw()
{
	clearScreen();

	// begin drawing sprites
	m_2dRenderer->begin();
	// draw your stuff here!
	aie::Gizmos::draw2D(glm::ortho<float>(-m_extents, m_extents, -m_extents / m_aspectRatio, m_extents / m_aspectRatio, -1.f, 1.f));
	//aie::Gizmos::draw2D(getWindowWidth(), getWindowHeight());
	m_gameStateManager->draw();

	char fps[32];
	sprintf_s(fps, 32, "FPS: %i", getFPS());
	m_2dRenderer->drawText(m_font, fps, 0, 720 - 32);

	// output some text, uses the last used colour
	m_2dRenderer->drawText(m_font, "Press ESC to quit", 0, 10);

	// done drawing sprites
	m_2dRenderer->end();

}