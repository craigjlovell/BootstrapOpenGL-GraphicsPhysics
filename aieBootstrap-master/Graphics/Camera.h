#pragma once
#include "glm/glm.hpp"
class Camera
{
public:

	Camera();
	~Camera();

	virtual void update(float deltaTime);

	glm::vec3 GetPosition() { return m_position; }

	glm::mat4 GetViewMatrix();

	glm::mat4 GetProjectionMatrix(float w, float h);

	glm::mat4 WorldTransform();

	

protected:

	float m_theta;
	float m_phi;
	glm::vec3 m_position;
	glm::vec4 m_rotation;

	float m_lastMouseX;
	float m_lastMouseY;
private:
};

