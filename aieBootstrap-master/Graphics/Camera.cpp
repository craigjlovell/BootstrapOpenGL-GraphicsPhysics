#include "Camera.h"
#include "glm/ext.hpp"
#include "Input.h"
#include <Gizmos.h>

Camera::Camera()
{
	m_theta = 0;
	m_phi = 0;
	m_position = glm::vec3(-10, 2, 0);
}

Camera::~Camera()
{
}

void Camera::update(float deltaTime)
{
	UpdateProjectionViewTransform();
}

void Camera::draw()
{
	aie::Gizmos::addSphere(GetPosition(), 0.1f, 10, 10, { 1,0,0,1 });
}

void Camera::SetPosition(glm::vec3 a_position)
{
	m_local[3].x = a_position.x;
	m_local[3].y = a_position.y;
	m_local[3].z = a_position.z;

	m_position = a_position;
}

glm::vec3 Camera::GetPosition()
{
	//glm::vec3 tempVec;
	//
	//tempVec.x = m_local[3].x;
	//tempVec.y = m_local[3].y;
	//tempVec.z = m_local[3].z;

	return m_position;
}

void Camera::SetRotation(glm::vec3 a_rotation)//, float angle)
{
	//m_transform = glm::rotate(MakeTransform(), glm::radians(angle), glm::vec3(0, 1, 0));
	glm::mat4 tempMat;
	
	float cosX = cos(glm::radians(a_rotation.x));
	float sinX = sin(glm::radians(a_rotation.x));

	m_local[1].y =  cosX - GetScale().y;
	m_local[1].z = -sinX;
	m_local[2].y =  sinX;
	m_local[2].z =  cosX + GetScale().z;

	float cosY = cos(glm::radians(a_rotation.y));
	float sinY = sin(glm::radians(a_rotation.y));

	m_local[0].x =  cosY + GetScale().x;
	m_local[0].z =  sinY;
	m_local[2].x = -sinY;
	m_local[2].z =  cosY - GetScale().z;

	float cosZ = cos(glm::radians(a_rotation.z));
	float sinZ = sin(glm::radians(a_rotation.z));

	m_local[0].x =  cosZ - GetScale().x;
	m_local[0].y = -sinZ;
	m_local[1].x =  sinZ;
	m_local[1].y =  cosZ - GetScale().y;

	m_rotation = a_rotation;
}

glm::vec3 Camera::GetRotation()
{
	glm::vec3 tempVec;

	glm::mat4 tempMat = 
	{
		1,0,0,0,
		0,1,0,0,
		0,0,1,0,
		0,0,0,1
	};

	glm::vec3 scale = GetScale();

	tempMat[0].x = m_local[0].x / scale.x;
	tempMat[1].x = m_local[1].x / scale.x;
	tempMat[2].x = m_local[2].x / scale.x;
								  
	tempMat[0].y = m_local[0].y / scale.y;
	tempMat[1].y = m_local[1].y / scale.y;
	tempMat[2].y = m_local[2].y / scale.y;
								  
	tempMat[0].z = m_local[0].z / scale.z;
	tempMat[1].z = m_local[1].z / scale.z;
	tempMat[2].z = m_local[2].z / scale.z;

	float t = tempMat[0].x + tempMat[1].y + tempMat[2].z;
	glm::vec4 q = {0.f, 0.f, 0.f, 0.f};

		if (t > 0) {
			float S = sqrt(t + 1.0) * 2;
			q.w = 0.25 * S;
			q.x = (tempMat[2].y - tempMat[1].z) / S;
			q.y = (tempMat[0].z - tempMat[2].x) / S;
			q.z = (tempMat[1].x - tempMat[0].y) / S;
		}
		else if (tempMat[0].x > tempMat[1].y && tempMat[0].x > tempMat[2].z)
		{
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
	m_local[0].x + a_scale.x;
	m_local[1].y + a_scale.y;
	m_local[2].z + a_scale.z;

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

	return m_scale;
}

void Camera::SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up)
{
	m_viewTransform = glm::lookAt(from, to, up);
}

void Camera::SetPerspective(float fieldOfView, float aspectRatio, float near, float far)
{
	m_projectionTransform = glm::perspective(glm::pi<float>() * fieldOfView, aspectRatio, near, far);
}

glm::mat4 Camera::GetWorldTransform()
{
	glm::mat4 tempMat =
	{
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};
	return m_local;
}

glm::mat4 Camera::GetProjectionView(float w, float h)
{
	return m_projectionViewTransform;
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
	m_projectionViewTransform = m_projectionTransform * m_viewTransform;
}

glm::mat4 Camera::GetTransform(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale)
{
	return glm::translate(glm::mat4(1), a_position)
		* glm::rotate(glm::mat4(1),
			glm::radians(a_eulerAngles.z), glm::vec3(0, 0, 1))
		* glm::rotate(glm::mat4(1),
			glm::radians(a_eulerAngles.y), glm::vec3(0, 1, 0))
		* glm::rotate(glm::mat4(1),
			glm::radians(a_eulerAngles.x), glm::vec3(1, 0, 0))
		* glm::scale(glm::mat4(1), a_scale);
}

glm::mat4 Camera::MakeTransform()
{
	return glm::translate(glm::mat4(1), m_position);
}



