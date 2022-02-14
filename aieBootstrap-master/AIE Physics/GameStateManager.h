#pragma once
#include "IGameState.h"
#include "App.h"

#include <map>
#include <list>
#include <functional>
#include "Font.h"

class IGameState;

class GameStateManager : public aie::Application
{
public:

	GameStateManager();
	virtual ~GameStateManager();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float dt);
	virtual void draw();

	void SetState(const char* name, IGameState* state);
	void PushState(const char* name);
	void PopState();

	IGameState* GetCurrentState();

protected:

	std::map<const char*, IGameState*> m_states;
	std::list<IGameState*> m_stack;

	std::list<std::function<void()> > m_commands;

private:
};