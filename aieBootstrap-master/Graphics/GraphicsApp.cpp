#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Planet.h"
#include "Mesh.h"
#include <imgui.h>

using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsApp::GraphicsApp() {

}

GraphicsApp::~GraphicsApp() {

}

bool GraphicsApp::startup() {
	
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_light.direction = { 1,-1,1 };
	m_light.color = { 1,1,1 };
	m_ambientLight = { 1.0f,1.0f,1.0f };

	return LaunchSahders();
}

void GraphicsApp::shutdown() {

	Gizmos::destroy();
}

void GraphicsApp::update(float deltaTime) {

	// wipe the gizmos clean for this frame
	Gizmos::clear();

	// draw a simple grid with gizmos
	vec4 white(1);
	vec4 black(0, 0, 0, 1);
	for (int i = 0; i < 21; ++i) {
		Gizmos::addLine(vec3(-10 + i, 0, 10),
						vec3(-10 + i, 0, -10),
						i == 10 ? white : black);
		Gizmos::addLine(vec3(10, 0, -10 + i),
						vec3(-10, 0, -10 + i),
						i == 10 ? white : black);
	}

	// add a transform so that we can see the axis
	Gizmos::addTransform(mat4(1));

	// Grab the time since the application started
	float time = getTime();

	// Rotate the light
	//m_light.direction = glm::normalize(glm::vec3(glm::cos(time * 2), glm::sin(time * 2), 0));
	

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	
	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Global Light Direction", &m_light.direction[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("Global Light Color", &m_light.color[0], 0.1f, 0.0f, 2.0f);
	ImGui::End();

	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_bunnyTransform = Rotation(m_bunnyTransform, 'y', -0.1f);
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_bunnyTransform = Rotation(m_bunnyTransform, 'y', 0.1f);

	//DrawPlanets();
}

void GraphicsApp::draw() {

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);

	//Bind the shader
	m_phongShader.bind();

	m_modelTransform = m_bunnyTransform;

	m_phongShader.bindUniform("AmbientColor", m_ambientLight);
	m_phongShader.bindUniform("LightColor", m_light.color);
	m_phongShader.bindUniform("LightDirection", m_light.direction);

	m_phongShader.bindUniform("CameraPosition", glm::vec3(glm::inverse(m_viewMatrix)[3]));

	// Bind the transform
	auto pvm = m_projectionMatrix * m_viewMatrix * m_modelTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	m_phongShader.bindUniform("ModelMatrix", m_modelTransform);

	// Draw the quad
	m_bunnyMesh.draw();

	// Bind the shader
	m_phongShader.bind();

	m_modelTransform = m_quadTransform;

	// Bind the transform
	pvm = m_projectionMatrix * m_viewMatrix * m_modelTransform;
	m_phongShader.bindUniform("ProjectionViewModel", pvm);

	// Simple binding for lightning data based on model used
	m_phongShader.bindUniform("ModelMatrix", m_modelTransform);

	// Draw quad
	m_quadMesh.draw();

	Gizmos::draw(m_projectionMatrix * m_viewMatrix);
}

glm::mat4 GraphicsApp::Rotation(glm::mat4 matrix, char axis, float rotationAmount)
{
	float cos = glm::cos(rotationAmount);
	float sin = glm::sin(rotationAmount);

	glm::mat4 tempMat;

	if (std::tolower(axis) == 'x')
	{
		tempMat =
		{
			1,		0,		0,		0,
			0,		cos,	-sin,	0,
			0,		sin,	cos,	0,
			0,		0,		0,		1
		};
	}
	if (std::tolower(axis) == 'y')
	{
		tempMat = {
			cos,	0,		sin,	0,
			0,		1,		0,		0,
			-sin,	0,		cos,	0,
			0,		0,		0,		1
		};
	}

	if (std::tolower(axis) == 'z')
	{
		tempMat = {
		cos, -sin,	0,	0,
		sin,  cos,	0,	0,
		0,	    0,	1,	0,
		0,		0,	0,	1
		};
	}

	return matrix * tempMat;
}

void GraphicsApp::DrawPlanets()
{
	Planet* sun = new Planet(glm::vec3(0, 0, 0), 1, glm::vec4(1,0.8,0,1), glm::vec3(0,0,0));
	sun->CreatePlanet();

	Planet* mercury = new Planet(glm::vec3(1.5, 0, 2), 0.24, glm::vec4(0, 0, 0.8, 1), glm::vec3(0, 0, 0));
	mercury->CreatePlanet();

	Planet* venus = new Planet(glm::vec3(3, 0, 0), 0.6, glm::vec4(0.8, 0, 0, 1), glm::vec3(0, 0, 0));
	venus->CreatePlanet();

	Planet* earth = new Planet(glm::vec3(4, 0, -1), 0.63, glm::vec4(0, .5, .5, 1), glm::vec3(0, 0, 0));
	earth->CreatePlanet();

	Planet* mars = new Planet(glm::vec3(5, 0, 1), 0.33, glm::vec4(1, 0, 0, 1), glm::vec3(0, 0, 0));
	mars->CreatePlanet();
	
	Planet* jupiter = new Planet(glm::vec3(6, 0, 0), 0.85, glm::vec4(0.5, 0, 0, 1), glm::vec3(0, 0, 0));
	jupiter->CreatePlanet();

	Planet* saturn = new Planet(glm::vec3(7, 0, 2), 0.8, glm::vec4(0.8, 1, 1, 1), glm::vec3(0, 0, 0));
	saturn->CreatePlanet();

	Planet* uranus = new Planet(glm::vec3(8, 0, -2), 0.75, glm::vec4(0.8, 0, 0, 1), glm::vec3(0, 0, 0));
	uranus->CreatePlanet();

	Planet* neptune = new Planet(glm::vec3(9, 0, 0), 0.7, glm::vec4(0.8, 0, 0, 1), glm::vec3(0, 0, 0));
	neptune->CreatePlanet();
}

bool GraphicsApp::LaunchSahders()
{
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	
	if (m_shader.link() == false)
	{
		printf("Simple Shader Error: %s\n", m_shader.getLastError());
		return false;
	}

	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");

	if (m_phongShader.link() == false)
	{
		printf("phong Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}

	Mesh::Vertex verticies[4];
	verticies[0].position = { -0.5 ,0 ,  0.5 ,1 };
	verticies[1].position = {  0.5 ,0 ,  0.5 ,1 };
	verticies[2].position = { -0.5 ,0 , -0.5 ,1 };
	verticies[3].position = {  0.5 ,0 , -0.5 ,1 };

	unsigned int indicies[6] = { 0,1,2,
								 2,1,3 };



	m_quadMesh.InitialiseQuad();
	m_quadTransform = { 10 ,0  ,0  ,0 ,
						0  ,10 ,0  ,0 ,
						0  ,0  ,10 ,0 ,
						0  ,0  ,0  ,1 };

	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny mesh error!\n");
		return false;
	}
	m_bunnyTransform = {
		0.5f ,0    ,0    ,0 ,
		0    ,0.5f ,0    ,0 ,
		0    ,0    ,0.5f ,0 ,
		0    ,0    ,0    ,1
	};

	//CreateHex();
	return true;
}

void GraphicsApp::CreateBox()
{
	Mesh::Vertex verticies[8];
	verticies[0].position = { -0.5 ,0.5 , 0.5 ,1 };
	verticies[1].position = {  0.5 ,0.5 , 0.5 ,1 };
	verticies[2].position = { -0.5 ,0.5 ,-0.5 ,1 };
	verticies[3].position = {  0.5 ,0.5 ,-0.5 ,1 };
								      	    
	verticies[4].position = { -0.5 ,-0.5 , 0.5 ,1 };
	verticies[5].position = {  0.5 ,-0.5 , 0.5 ,1 };
	verticies[6].position = { -0.5 ,-0.5 ,-0.5 ,1 };
	verticies[7].position = {  0.5 ,-0.5 ,-0.5 ,1 };

	unsigned int indicies[36] = {
								 0,1,2,2,1,3, // top
								 0,4,1,1,4,5, // left front
								 2,6,0,0,6,4, // back left
								 3,7,2,2,7,6, // back right
								 1,5,3,3,5,7, // right front
								 5,4,7,7,4,6  // bottom
	};

	m_quadMesh.Initialise(8, verticies, 36, indicies);
}

void GraphicsApp::CreatePyramid()
{
	Mesh::Vertex verticies[5];
	verticies[0].position = { -0.5 ,-0.5 , 0.5 ,1 };
	verticies[1].position = { 0.5 ,-0.5 , 0.5 ,1 };
	verticies[2].position = { -0.5 ,-0.5 ,-0.5 ,1 };
	verticies[3].position = { 0.5 ,-0.5 ,-0.5 ,1 };

	verticies[4].position = { 0,0.5,0,1 };

	unsigned int indicies[18] = {
								 5,4,7,7,4,6, // bottom
								 2,4,0,
								 3,4,2,
								 3,4,1,
								 1,4,0};

	m_quadMesh.Initialise(5, verticies, 18, indicies);
}

void GraphicsApp::CreateHex()
{
	Mesh::Vertex verticies[6];
	verticies[0].position = { -0.5f, 0.0f, -1.0f, 1};
	verticies[1].position = { 0.5f, 0.0f, -1.0f,1   };
	verticies[2].position = { 1.0f, 0.0f, 0.0f,1   };
	verticies[3].position = { 0.5f, 0.0f, 1.0f,1  };
	verticies[4].position = { -0.5f, 0.0f, 1.0f,1};
	verticies[5].position = { -1.0f, 0.0f, 0.0f, 1};

	unsigned int indicies[18] = {
								 1,6,0,
								 6,5,0,
								 5,4,0,
								 4,3,0,
								 3,2,0,
								 2,1,0};

	m_quadMesh.Initialise(6, verticies, 18, indicies);
}

void GraphicsApp::CreateGrid()
{

}