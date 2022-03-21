#pragma once
#include "Camera.h"

class FlyCamera : public Camera
{
public:
	float m_speed;
	FlyCamera();
	~FlyCamera();

	virtual void update(float a_deltaTime);

	void SetSpeed();
	float Getspeed() { return m_speed; };

protected:

	

private:
};

