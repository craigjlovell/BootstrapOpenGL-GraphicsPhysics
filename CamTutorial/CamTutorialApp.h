#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Camera.h"

class Camera;

class CamTutorialApp : public aie::Application {
public:

	CamTutorialApp();
	virtual ~CamTutorialApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;

	Camera m_cam;
};