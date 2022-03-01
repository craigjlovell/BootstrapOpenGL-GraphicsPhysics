#include "GameState.h"
#include "AIE_PhysicsApp.h"
#include "App.h"

#include "GameStateManager.h"

GameState::GameState(App* a_app) : m_app(a_app)
{

}

GameState::~GameState()
{

}

bool GameState::startup()
{
	m_physApp = new AIE_PhysicsApp();
	m_physApp->startup(m_app);

	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	std::cout << "Loading game" << std::endl;


	return true;

}

void GameState::shutdown()
{
	m_physApp->shutdown();
	delete m_physApp;
	m_physApp = nullptr;

	delete m_font;
	delete m_2dRenderer;
	std::cout << "Unloading Menu" << std::endl;

}

void GameState::update(float dt)
{
	m_physApp->update(dt);

	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Game");
	}
}

void GameState::draw()
{
	
	m_2dRenderer->begin();
	m_2dRenderer->drawText(m_font, "Billards ", 0, 720 - 100);
	m_physApp->draw();
	m_2dRenderer->end();
}

