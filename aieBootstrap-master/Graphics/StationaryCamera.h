#pragma once
#include "Camera.h"
class StationaryCamera : public Camera
{
public:

	StationaryCamera();
	StationaryCamera(glm::vec3 pos, glm::mat4 rot);
	~StationaryCamera();


protected:

private:

};

