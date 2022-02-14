#pragma once

#include "IGameState.h"
#include <Input.h>
#include "Renderer2D.h"

class App;
class AIE_PhysicsApp;

class GameState : public IGameState
{
public:

	GameState(App* a_app);
	virtual ~GameState();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float dt);
	virtual void draw();

protected:
	App* m_app;
	AIE_PhysicsApp* m_physApp = nullptr;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

private:

	

};