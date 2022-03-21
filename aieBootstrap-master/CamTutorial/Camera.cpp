#include "Camera.h"
#include "glm/ext.hpp"
#include <Input.h>

Camera::Camera()
{
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));
	glm::vec3 up(0, 1, 0);

	if (input->isKeyDown(aie::INPUT_KEY_X))
		m_position += up * deltaTime;

	float mx = input->getMouseX();
	float my = input->getMouseY();

	const float turnSpeed = 0.1f;

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_theta += turnSpeed * (mx - m_lastMouseX);
		m_phi -= turnSpeed * (my - m_lastMouseY);
	}
	m_lastMouseX = mx;
	m_lastMouseY = my;

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
