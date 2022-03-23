#pragma once
#include "Camera.h"
class StationaryCamera : public Camera
{
public:

	StationaryCamera();
	StationaryCamera(glm::vec3 a_position, glm::vec3 rot);
	~StationaryCamera();
	


protected:

	glm::mat4 matrix;

private:

};

