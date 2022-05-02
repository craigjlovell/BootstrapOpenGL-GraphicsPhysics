#include "MenuState.h"
#include "GameStateManager.h"
#include "Gizmos.h"
#include <iostream>



MenuState::MenuState(App* a_app) : m_app(a_app)
{

}

MenuState::~MenuState()
{

}

bool MenuState::startup()
{
	m_2dRenderer = new aie::Renderer2D();
	m_font = new aie::Font("../bin/font/consolas.ttf", 32);
	std::cout << "Loading Menu" << std::endl;
	return true;
}

void MenuState::shutdown()
{
	delete m_font;
	delete m_2dRenderer;
	std::cout << "Unloading Menu" << std::endl;
}

void MenuState::update(float dt)
{
	aie::Input* input = aie::Input::getInstance();
	if (input->wasKeyPressed(aie::INPUT_KEY_SPACE))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Game");
	}
}

void MenuState::draw()
{
	m_app->clearScreen();
	m_2dRenderer->begin();
	

	m_2dRenderer->setRenderColour(0.8f, 0.f, 0.5f, 1.f);
	m_2dRenderer->drawBox(m_app->getWindowWidth() / 2, m_app->getWindowHeight() / 2, m_app->getWindowWidth()/2, m_app->getWindowHeight()/2, 0, 0);
	m_2dRenderer->setRenderColour(0.f, 1.f, 0.f, 1.f);
	m_2dRenderer->drawText(m_font, "MenuScreen ", m_app->getWindowWidth() / 2 - 100, m_app->getWindowHeight() / 2, 0);
	m_2dRenderer->setRenderColour(0.f, 0.f, 1.f, 1.f);
	m_2dRenderer->drawText(m_font, "Press Space To Play ", m_app->getWindowWidth() / 2 - 165, m_app->getWindowHeight() / 2 - 50, 0);
	
	m_2dRenderer->end();
}