#pragma once
#include "Camera.h"
class StationaryCamera : public Camera
{
public:

	StationaryCamera();
	StationaryCamera(glm::mat4 mat, glm::vec3 a_position, float deg, glm::vec3 rot);
	~StationaryCamera();
	glm::mat4 matrix;


protected:

private:

};

