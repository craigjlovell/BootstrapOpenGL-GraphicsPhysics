#include "StationaryCamera.h"
#include "glm/ext.hpp"

StationaryCamera::StationaryCamera()
{
	m_position = glm::vec3{ -8,2,0 };;
}
StationaryCamera::StationaryCamera(glm::mat4 mat, glm::vec3 a_position, float deg, glm::vec3 rot)
{
	//m_rotation = glm::mat4 matrix;
	glm::mat4 matrix;
	matrix = glm::rotate(matrix, glm::radians(180.0f), glm::vec3(0.0f, 0.0f, 1.0f));
}

StationaryCamera::~StationaryCamera()
{
	
}