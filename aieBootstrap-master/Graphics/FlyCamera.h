#pragma once
#include "Camera.h"

class FlyCamera : public Camera
{
public:

	
	FlyCamera();
	~FlyCamera();

	virtual void update(float a_deltaTime);

	void SetSpeed(float _speed) { m_speed = _speed; }
	float GetSpeed() { return m_speed; }

protected:

	float m_speed;

private:
};

