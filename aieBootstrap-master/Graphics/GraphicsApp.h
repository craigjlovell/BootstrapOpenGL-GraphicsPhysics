#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>
#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"


class GraphicsApp : public aie::Application {
public:

	GraphicsApp();
	virtual ~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	void DrawPlanets();

protected:

	bool LaunchSahders();

	void CreateBox();

	void CreatePyramid();

	void CreateHex();

	aie::ShaderProgram m_shader;

	// Generic quad data
	Mesh		m_quadMesh;
	glm::mat4	m_quadTransform;

	// Standford Bunny Data
	aie::OBJMesh	m_bunnyMesh;
	glm::mat4		m_bunnyTransform;

	// camera transforms
	glm::mat4	m_viewMatrix;
	glm::mat4	m_projectionMatrix;
};