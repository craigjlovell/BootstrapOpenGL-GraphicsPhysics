#include "FlyCamera.h"
#include "Input.h"
#include "imgui.h"

FlyCamera::FlyCamera()
{
	m_speed = 5.0f;
}

FlyCamera::~FlyCamera()
{

}

void FlyCamera::update(float a_deltaTime)
{
	aie::Input* input = aie::Input::getInstance();
	float thetaR = glm::radians(m_theta);
	float phiR = glm::radians(m_phi);

	glm::vec3 up(0, 1, 0);
	glm::vec3 forward(cos(phiR) * cos(thetaR), sin(phiR), cos(phiR) * sin(thetaR));
	glm::vec3 right(-sin(thetaR), 0, cos(thetaR));

	if (input->isKeyDown(aie::INPUT_KEY_Z))
		m_position += up * a_deltaTime * m_speed;
	if (input->isKeyDown(aie::INPUT_KEY_X))
		m_position -= up * a_deltaTime * m_speed;
	if (input->isKeyDown(aie::INPUT_KEY_D))
		m_position += right * a_deltaTime * m_speed;
	if (input->isKeyDown(aie::INPUT_KEY_A))
		m_position -= right * a_deltaTime * m_speed;
	if (input->isKeyDown(aie::INPUT_KEY_W))
		m_position += forward * a_deltaTime * m_speed;
	if (input->isKeyDown(aie::INPUT_KEY_S))
		m_position -= forward * a_deltaTime * m_speed;

	float mx = input->getMouseX();
	float my = input->getMouseY();

	const float turnSpeed = 0.1f;

	if (input->isMouseButtonDown(aie::INPUT_MOUSE_BUTTON_RIGHT))
	{
		m_theta += turnSpeed * (mx - m_lastMouseX);
		m_phi -= -turnSpeed * (my - m_lastMouseY);
	}
	m_lastMouseX = mx;
	m_lastMouseY = my;
	//SetSpeed();
}

//void FlyCamera::SetSpeed()
//{
//	ImGui::Begin("Speed Settings");
//	ImGui::DragFloat("Speed", &m_speed, 0.1f, 1.0f, 100.0f);
//	ImGui::End();
//}
