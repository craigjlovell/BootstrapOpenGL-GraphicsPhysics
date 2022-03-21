#pragma once
#include "Camera.h"
class StationaryCamera : public Camera
{
public:

	StationaryCamera();
	~StationaryCamera();

	virtual void update();

	void SetPosition();


protected:

	glm::vec3 m_position;

private:

};

