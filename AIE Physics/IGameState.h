#pragma once


class IGameState
{
public:

	IGameState() {}
	virtual ~IGameState() {}

	virtual bool startup() { return true; }
	virtual void shutdown() {}

	virtual void update(float dt) {}
	virtual void draw() {}

protected:
private:
};