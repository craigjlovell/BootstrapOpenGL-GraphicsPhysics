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

void Camera::SetPosition(glm::vec3 a_position)
{
	glm::mat4 tempMat{
		1, 0, 0, a_position.x,
		0, 1, 0, a_position.y,
		0, 0, 1, a_position.z,
		0, 0, 0, 1
	};

	m_localTransform *= tempMat;

	m_position = a_position;
}

void Camera::SetRotation(glm::vec3 a_rotation)
{
	float _cos = 0;
	float _sin = 0;

	glm::mat4 tempMat;
	// X
	_cos = cos(glm::radians(a_rotation.x));
	_sin = sin(glm::radians(a_rotation.x));
	tempMat = {
		1,		0,		0,		0,
		0,		_cos,	-_sin,	0,
		0,		_sin,	_cos,	0,
		0,		0,		0,		1
	};
}

void Camera::SetScale(glm::vec3 a_scale)
{
	glm::mat4 tempMat;
	tempMat = {
		a_scale.x,		   0,		  0,		0,
				0, a_scale.y,		  0,		0,
				0,		   0, a_scale.z,		0,
				0,		   0,		  0,		1
	};

	m_local *= tempMat;

	a_scale = m_scale;
}

void Camera::SetLookAt(glm::vec3 form, glm::vec3 to, glm::vec3 up)
{
}

void Camera::SetPerspective(float fieldOfView, float aspectRatio, float, float)
{
}

glm::mat4 Camera::GetWorldTransform()
{
	return glm::mat4();
}

//glm::mat4 Camera::GetView()
//{
//	return glm::mat4();
//}

//glm::mat4 Camera::GetProjection(float w, float h)
//{
//	return glm::mat4();
//}

glm::mat4 Camera::GetProjectionView(float w, float h)
{
	return GetViewMatrix() * GetProjectionMatrix(w, h);
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

void Camera::UpdateProjectionViewTransform()
{
}



