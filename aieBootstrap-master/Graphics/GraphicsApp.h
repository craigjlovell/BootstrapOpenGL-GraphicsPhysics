#pragma once

#include "Application.h"
#include <vector>
#include <glm/mat4x4.hpp>

#include "Shader.h"
#include "Mesh.h"
#include "OBJMesh.h"

#include "Camera.h"
#include "FlyCamera.h"
#include "StationaryCamera.h"

#include "RenderTarget.h"
#include "ParticleEmitter.h"

class Scene;
class Instance;
class Camera;

enum PostProcessingEffect
{
	DEFAULT = 0,
	BOX_BLUR,
	DISTORT,
	EDGE_DETECTION,
	SEPIA,
	SCAN_LINES,
	GREY_SCALE,
	INVERT,
	PIXILIZER,
	POSTERIZATION,
	DISTANCE_FOG,
	DEPTH_OF_VIEW
};

class GraphicsApp : public aie::Application {
public:

	GraphicsApp();
	virtual ~GraphicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::mat4 Rotation(glm::mat4 matrix, char axis, float rotationAmount);

	glm::vec3 scale;

protected:

	bool isFly = false;
	bool isStatinary = false;

	float m_dt = 0;

	glm::vec3 t_rotation;
	glm::vec3 t_scale;
	glm::vec3 t_position;
	glm::vec3 t_rotation2;
	glm::vec3 t_scale2;
	glm::vec3 t_position2;


	bool LaunchSahders();

	void CreateBox();

	void CreatePyramid();

	void CreateHex();

	void CreateGrid();
	
	Instance*			m_raygunIns;

	aie::Texture		m_gridTexture;
	aie::Texture		m_spearTexture;
	aie::Texture		m_pokemon;

	aie::Texture		m_marbleTexture;
	aie::Texture		m_hatchingTexture;
	aie::Texture		m_rampTexture;

	aie::ShaderProgram	m_shader;
	aie::ShaderProgram	m_phongShader;
	aie::ShaderProgram	m_phongExtShader;
	aie::ShaderProgram	m_texturedShader;
	aie::ShaderProgram	m_normalMapShader;
	aie::ShaderProgram	m_postShader;
	aie::ShaderProgram	m_advancePostShader;
	aie::ShaderProgram	m_particleShader;

	aie::RenderTarget	m_renderTarget;

	std::vector<Camera*>				m_cameras;
	int camIndex;
	FlyCamera*			m_flyCamera;
	StationaryCamera	m_stationaryCamera;

	// For Post-Processing
	Mesh				m_screenQuad;
	int					m_postProcessEffect = PostProcessingEffect::DEFAULT;
	glm::mat4			m_modelTransform;

	// Generic quad data
	Mesh				m_quadMesh;
	glm::mat4			m_quadTransform;

	// Generic Cube data
	Mesh				m_cubeMesh;
	glm::mat4			m_cubeTransform;

	// Generic Pyra data
	Mesh				m_pyMesh;
	glm::mat4			m_pyTransform;

	// Generic hex data
	Mesh				m_hexMesh;
	glm::mat4			m_hexTransform;

	// Generic grid data
	Mesh				m_gridMesh;
	glm::mat4			m_gridTransform;

	// Standford Bunny Data
	aie::OBJMesh		m_bunnyMesh;
	glm::mat4			m_bunnyTransform;

	// Soulspear data
	aie::OBJMesh		m_spearMesh;
	glm::mat4			m_spearTransform;

	// RayGun
	aie::OBJMesh		m_raygunMesh;
	glm::mat4			m_raygunTransform;

	// camera transforms
	glm::mat4			m_viewMatrix;
	glm::mat4			m_projectionMatrix;

	// Light Setup
	glm::vec3			m_ambientLight;

	Scene*				m_scene;

	ParticleEmitter*	m_emitter;
	glm::mat4			m_particleTransform;
	
};