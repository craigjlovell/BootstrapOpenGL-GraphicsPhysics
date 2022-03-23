#include "StationaryCamera.h"
#include "glm/ext.hpp"

StationaryCamera::StationaryCamera()
{
	
}
StationaryCamera::StationaryCamera(glm::vec3 a_position, glm::vec3 rot)
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	m_position = glm::vec3{ -5,2,0 };
	m_phi = 10;
	m_theta = 10; 
	m_rotation = { 10,0,0 };
}

StationaryCamera::~StationaryCamera()
{
	
}