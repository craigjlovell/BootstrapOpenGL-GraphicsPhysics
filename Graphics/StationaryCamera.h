#pragma once
#include "Camera.h" 

class StationaryCamera : public Camera
{
public:

	StationaryCamera();
	StationaryCamera(glm::vec3 a_position, glm::vec3 rot);
	~StationaryCamera();

	virtual void update(float deltaTime);
	


protected:
	Camera* m_camera;

	glm::mat4 matrix;

private:

};

