#pragma once
#include "glm/glm.hpp"

class Camera
{
public:

	Camera();
	Camera(glm::vec3 a_position);
	~Camera();

	virtual void update(float deltaTime = 0);

	virtual void draw();

	void SetPosition(glm::vec3 a_position);
	glm::vec3 GetPosition();// couldnt i just return m_pos 
							//and ignore the function and set
							// it in set then set m to = a


	void SetRotation(glm::vec3 a_rotation);//, float angle);
	glm::vec3 GetRotation();

	void SetScale(glm::vec3 a_scale);
	glm::vec3 GetScale();

	void SetLookAt(glm::vec3 from, glm::vec3 to, glm::vec3 up);
	void SetPerspective(float fieldOfView, float aspectRatio, float near, float far);

	glm::mat4 GetLocalTransform() { return m_local; }
	glm::mat4 GetWorldTransform();

	glm::mat4 GetProjectionView(float w, float h);
	glm::mat4 GetViewMatrix();
	glm::mat4 GetProjectionMatrix(float w, float h);

	glm::mat4 GetTransform(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale);

	//glm::mat4 MakeTransform() { return m_transform; };
	glm::mat4 MakeTransform();

protected:

	glm::mat4 m_worldTransform;
	glm::mat4 m_projectionTransform;
	glm::mat4 m_projectionViewTransform;
	glm::mat4 m_viewTransform;

	float m_theta;
	float m_phi;

	glm::vec3 m_position;
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_transform;

	float m_lastMouseX;
	float m_lastMouseY;

	glm::mat4 m_local =
	{
			1,	0,	0,	0,	// 0
			0,	1,	0,	0,	// 1
			0,	0,	1,	0,	// 2
			0,	0,	0,	1	// 3
	};//	x	y	z	w

private:
	void UpdateProjectionViewTransform();
};
