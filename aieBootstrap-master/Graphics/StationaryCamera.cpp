#include "StationaryCamera.h"
#include "glm/ext.hpp"

StationaryCamera::StationaryCamera()
{
	
}
StationaryCamera::StationaryCamera(glm::vec3 a_position, glm::vec3 rot)
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	m_position = glm::vec3{ -10,2,0 };
	m_phi = 5;
	m_theta = 5; 
	//m_rotation = { 10,0,0 };
}

StationaryCamera::~StationaryCamera()
{
	
}