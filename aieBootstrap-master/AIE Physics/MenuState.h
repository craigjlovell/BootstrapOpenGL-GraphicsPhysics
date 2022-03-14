#pragma once
#include "App.h"
#include "IGameState.h"
#include <Input.h>

class App;

class MenuState : public IGameState
{
public:

	MenuState(App* a_app);
	virtual ~MenuState();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float dt);
	virtual void draw();

protected:

	App* m_app;
	
	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

private:

};