#pragma once
#include "Application.h"
#include "Renderer2D.h"


class GameStateManager;

class App : public aie::Application
{
public:

	App();
	virtual ~App();
	virtual bool startup();
	virtual void shutdown();
	virtual void update(float deltaTime);
	virtual void draw();

	GameStateManager* GetGameStateManager()
	{
		return m_gameStateManager;
	}

protected:

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;


	const float m_extents = 100;
	const float m_aspectRatio = 16.f / 9.f;

private:
	GameStateManager* m_gameStateManager = nullptr;
	
};

