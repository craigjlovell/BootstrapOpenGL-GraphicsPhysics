#include "Camera.h"
#include "glm/ext.hpp"
#include "Input.h"

Camera::Camera()
{
	m_theta = 0;
	m_phi = 0;
	m_position = {-10, 2, 0};
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	

}

glm::mat4 Camera::GetViewMatrix()
{
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	return glm::lookAt(m_position, m_position + forward, glm::vec3(0, 1, 0));
}

glm::mat4 Camera::GetProjectionMatrix(float w, float h)
{
	return glm::perspective(glm::pi<float>() * 0.25f, w / h, 0.1f, 1000.0f);
}

