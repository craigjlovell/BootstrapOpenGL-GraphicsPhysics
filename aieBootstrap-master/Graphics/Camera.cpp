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
	m_local[0].x = a_position.x;
	m_local[1].x = a_position.y;
	m_local[2].x = a_position.z;

	m_position = a_position;
}

void Camera::SetRotation(glm::vec3 a_rotation)
{
	glm::mat4 tempMat;
	
	float _cosX = cos(glm::radians(a_rotation.x));
	float _sinX = sin(glm::radians(a_rotation.x));

	m_local[1].y =  _cosX - GetScale().y;
	m_local[1].z = -_sinX;
	m_local[2].y =  _sinX;
	m_local[2].z =  _cosX + GetScale().z;

	float _cosY = cos(glm::radians(a_rotation.y));
	float _sinY = sin(glm::radians(a_rotation.y));

	m_local[0].x =  _cosY + GetScale().x;
	m_local[0].z =  _sinY;
	m_local[2].x = -_sinY;
	m_local[2].z =  _cosY - GetScale().z;

	float _cosZ = cos(glm::radians(a_rotation.z));
	float _sinZ = sin(glm::radians(a_rotation.z));

	m_local[0].x =  _cosZ - GetScale().x;
	m_local[0].y = -_sinZ;
	m_local[1].x =  _sinZ;
	m_local[1].y =  _cosZ + GetScale().y;

	m_rotation = a_rotation;
}

glm::vec3 Camera::GetRotation()
{
	glm::mat4 tempMat;
	glm::vec3 tempVec;

	tempMat = {
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	glm::vec3 Scale = GetScale();

	tempMat[0].x = m_local[0].x / Scale.x;
	tempMat[1].x = m_local[1].x / Scale.x;
	tempMat[2].x = m_local[2].x / Scale.x;

	tempMat[0].y = m_local[0].y / Scale.y;
	tempMat[1].y = m_local[1].y / Scale.y;
	tempMat[2].y = m_local[2].y / Scale.y;

	tempMat[0].z = m_local[0].z / Scale.z;
	tempMat[1].z = m_local[1].z / Scale.z;
	tempMat[2].z = m_local[2].z / Scale.z;

	float t = tempMat[0].x + tempMat[1].y + tempMat[2].z;
	glm::vec4 q = {0, 0, 0, 0};

		if (t > 0) {
			float S = sqrt(t + 1.0) * 2;
			q.w = 0.25 * S;
			q.x = (tempMat[2].y - tempMat[1].z) / S;
			q.y = (tempMat[0].z - tempMat[2].x) / S;
			q.z = (tempMat[1].x - tempMat[0].y) / S;
		}
		else if ((tempMat[0].x > tempMat[1].y) & (tempMat[0].x > tempMat[2].z)) {
			float S = sqrt(1.0 + tempMat[0].x - tempMat[1].y - tempMat[2].z) * 2; // S=4*qx 
			q.w = (tempMat[2].y - tempMat[1].z) / S;
			q.x = 0.25 * S;
			q.y = (tempMat[0].y + tempMat[1].x) / S;
			q.z = (tempMat[0].z + tempMat[2].x) / S;
		}
		else if (tempMat[1].y > tempMat[2].z) {
			float S = sqrt(1.0 + tempMat[1].y - tempMat[0].x - tempMat[2].z) * 2; // S=4*qy
			q.w = (tempMat[0].z - tempMat[2].x) / S;
			q.x = (tempMat[0].y + tempMat[1].x) / S;
			q.y = 0.25 * S;
			q.z = (tempMat[1].z + tempMat[2].y) / S;
		}
		else {
			float S = sqrt(1.0 + tempMat[2].z - tempMat[0].x - tempMat[1].y) * 2; // S=4*qz
			q.w = (tempMat[1].x - tempMat[0].y) / S;
			q.x = (tempMat[0].z + tempMat[2].x) / S;
			q.y = (tempMat[1].z + tempMat[2].y) / S;
			q.z = 0.25 * S;
		}
		return m_rotation;
}

void Camera::SetScale(glm::vec3 a_scale)
{
	m_local[0].x = a_scale.x;
	m_local[1].x = a_scale.y;
	m_local[2].x = a_scale.z;

	m_scale = a_scale;
}

glm::vec3 Camera::GetScale()
{
	glm::vec3 tempVec;

	glm::vec3 x(m_local[0].x, m_local[1].x, m_local[2].x);
	glm::vec3 y(m_local[0].y, m_local[1].y, m_local[2].y);
	glm::vec3 z(m_local[0].z, m_local[1].z, m_local[2].z);

	tempVec.x = glm::length(x);
	tempVec.y = glm::length(y);
	tempVec.z = glm::length(z);

	return tempVec;
}

void Camera::SetLookAt(glm::vec3 form, glm::vec3 to, glm::vec3 up)
{
}

void Camera::SetPerspective(float fieldOfView, float aspectRatio, float, float)
{
}

glm::mat4 Camera::GetWorldTransform()
{
	glm::mat4 tempMat{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return m_local;
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



