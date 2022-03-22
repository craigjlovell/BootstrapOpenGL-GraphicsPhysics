#pragma once

#include "Application.h"
#include <glm/mat4x4.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

#include "Camera.h"
#include "FlyCamera.h"
#include "StationaryCamera.h"

class GraphicsApp : public aie::Application {
public:

	GraphicsApp();
	virtual ~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::mat4 Rotation(glm::mat4 matrix, char axis, float rotationAmount);

	glm::mat4 MakeScale(glm::mat4 matrix, char axis, float x, float y, float z);

	void DrawPlanets();

protected:

	bool LaunchSahders();

	void CreateBox();

	void CreatePyramid();

	void CreateHex();

	void CreateGrid();
	
	aie::Texture		m_gridTexture;
	aie::Texture		m_spearTexture;
	aie::Texture		m_pokemon;

	aie::ShaderProgram	m_shader;
	aie::ShaderProgram	m_phongShader;
	aie::ShaderProgram	m_texturedShader;
	aie::ShaderProgram	m_normalMapShader;

	Camera				m_camera;
	FlyCamera			m_flyCamera;
	StationaryCamera	m_statCam;

	glm::mat4			m_modelTransform;

	// Generic quad data
	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;

	// Standford Bunny Data
	aie::OBJMesh		m_bunnyMesh;
	glm::mat4			m_bunnyTransform;

	// Soulspear data
	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;

	// RayGun
	aie::OBJMesh		m_pokemonMesh;
	glm::mat4			m_pokemonTransform;

	// camera transforms
	glm::mat4			m_viewMatrix;
	glm::mat4			m_projectionMatrix;

	struct Light
	{
		glm::vec3 direction;
		glm::vec3 color;
	};

	Light m_light;
	glm::vec3 m_ambientLight;

};