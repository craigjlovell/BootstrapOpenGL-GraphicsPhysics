#include "MenuState.h"
#include "GameStateManager.h"
#include "App.h"

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
	if (input->wasKeyPressed(aie::INPUT_KEY_ENTER))
	{
		m_app->GetGameStateManager()->PopState();
		m_app->GetGameStateManager()->PushState("Game");
	}
}

void MenuState::draw()
{
	m_app->clearScreen();
	m_2dRenderer->begin();
	m_2dRenderer->drawText(m_font, "MenuScreen ", 0, 720 - 100);
	m_2dRenderer->end();
}