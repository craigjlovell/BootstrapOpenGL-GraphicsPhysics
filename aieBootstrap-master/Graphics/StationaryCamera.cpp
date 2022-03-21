#include "StationaryCamera.h"

StationaryCamera::StationaryCamera()
{
	m_position = glm::vec3{ -10,2,0 };
}
StationaryCamera::StationaryCamera(glm::vec3 pos, glm::mat4 rot)
{
	pos = { -10,2,0 };
	rot = {
		0,0,0,0,
		0,0,0,0,
		0,0,0,0,
		0,0,0,0 };
}

StationaryCamera::~StationaryCamera()
{
	
}