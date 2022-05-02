#include "StationaryCamera.h"
#include "glm/ext.hpp"

StationaryCamera::StationaryCamera()
{
	
}
StationaryCamera::StationaryCamera(glm::vec3 a_position, glm::vec3 rot)
{
	
}

StationaryCamera::~StationaryCamera()
{
	
}

void StationaryCamera::update(float deltaTime)
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	m_position = glm::vec3{ -5.7f,2,-5.6f };
	m_phi = 1.7f;
	m_theta = 46.4f;
}