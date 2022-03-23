#include "GraphicsApp.h"
#include "Gizmos.h"
#include "Input.h"
#include <glm/glm.hpp>
#include <glm/ext.hpp>
#include "Planet.h"
#include "imgui.h"
#include "Instance.h"
#include "Scene.h"


using glm::vec3;
using glm::vec4;
using glm::mat4;
using aie::Gizmos;

GraphicsApp::GraphicsApp() 
{

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

	// Default Light Values
	Light light;
	light.direction = { 1, -1, 1 };
	light.color = { 1, 1, 1 };
	m_ambientLight = { 1.0f, 1.0f, 1.0f };

	m_scene = new Scene(&m_statCam, glm::vec2(getWindowWidth(), getWindowHeight()), light, m_ambientLight);

	m_scene->AddPointLights(glm::vec3(5, 3, 0), glm::vec3(1, 0, 0), 50);
	m_scene->AddPointLights(glm::vec3(-5, 3, 0), glm::vec3(0, 0, 1), 50);

	m_statCam = StationaryCamera(glm::vec3{ -10,2,0 }, m_camera.GetRotation());

	return LaunchSahders();
}

void GraphicsApp::shutdown() {

	Gizmos::destroy();
	delete m_scene;
}

void GraphicsApp::update(float deltaTime) {

	m_camera.update(deltaTime);
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

	ImGui::Begin("Light Settings");
	ImGui::DragFloat3("Global Light Direction", &m_scene->GetGlobalLight().direction[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("Global Light Color", &m_scene->GetGlobalLight().color[0], 0.1f, 0.0f, 20.0f);
	ImGui::End();

	m_flyCamera.SetSpeed();
	m_flyCamera.update(deltaTime);

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_bunnyTransform = Rotation(m_bunnyTransform, 'y', -0.1f);
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_bunnyTransform = Rotation(m_bunnyTransform, 'y', 0.1f);

	//DrawPlanets();
}

void GraphicsApp::draw() 
{
	// We nered to bind our rendertarget first
	//m_renderTarget.bind();

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	glm::mat4 projectionMatrix = m_statCam.GetProjectionMatrix(getWindowWidth(), (float)getWindowHeight());
	glm::mat4 viewMatrix = m_statCam.GetViewMatrix();
	auto pvm = projectionMatrix * viewMatrix * m_modelTransform;

	m_scene->Draw();
	
	// Unbind the target to return it to the back bufffer
	//m_renderTarget.unbind();

	//clearScreen();

	#pragma region Textured Quad Mesh
	// Bind the shader
	m_texturedShader.bind();

	m_modelTransform = m_quadTransform;

	// Bind the transform
	pvm = projectionMatrix * viewMatrix * m_modelTransform;
	m_texturedShader.bindUniform("ProjectionViewModel", pvm);

	// Bind the texture at the location
	m_texturedShader.bindUniform("diffuseTexture", 0);

	//m_renderTarget.getTarget(0).bind(0);

	// Bind the texture to the specific location
	m_gridTexture.bind(0);

	// Draw quad
	m_quadMesh.draw();
	#pragma endregion

	Gizmos::draw(projectionMatrix * viewMatrix);
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
			cos,	-sin,	0,		0,
			sin,	 cos,	0,		0,
			0,		 0,		1,		0,
			0,		 0,		0,		1
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
	if (m_renderTarget.initialise(1, getWindowWidth(), getWindowHeight()) == false);
	{

	}


#pragma region LaunchShaders

	#pragma region Shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	if (m_shader.link() == false)
	{
		printf("Simple Shader Error: %s\n", m_shader.getLastError());
		return false;
	}
	#pragma endregion

	#pragma region PhongShader
	m_phongShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phong.vert");
	m_phongShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phong.frag");
	if (m_phongShader.link() == false)
	{
		printf("Phong Shader Error: %s\n", m_phongShader.getLastError());
		return false;
	}
	#pragma endregion

	#pragma region TexturedShader/GridShader
	m_texturedShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/textured.vert");
	m_texturedShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/textured.frag");
	if (m_texturedShader.link() == false)
	{
		printf("Textured Shader Error: %s\n", m_texturedShader.getLastError());
		return false;
	}

	if (m_gridTexture.load("./textures/numbered_grid.tga") == false)
	{
		printf("failed to load the textures, please check file path!\n");
		return false;
	}
	#pragma endregion

	#pragma region NormalMap
	m_normalMapShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/normalMap.vert");
	m_normalMapShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/normalMap.frag");
	if (m_normalMapShader.link() == false)
	{
		printf("Normal Map Shader Error: %s\n", m_normalMapShader.getLastError());
		return false;
	}
	#pragma endregion

	Mesh::Vertex verticies[4];
	verticies[0].position = { -0.5 ,0 ,  0.5 ,1 };
	verticies[1].position = { 0.5 ,0 ,  0.5 ,1 };
	verticies[2].position = { -0.5 ,0 , -0.5 ,1 };
	verticies[3].position = { 0.5 ,0 , -0.5 ,1 };

	unsigned int indicies[6] = { 0, 1, 2, 2, 1, 3 };

	#pragma region Quad Mesh / Transform
	m_quadMesh.InitialiseQuad();
	m_quadTransform = {
		10 ,0  ,0  ,0 ,
		0  ,10 ,0  ,0 ,
		0  ,0  ,10 ,0 ,
		0  ,0  ,0  ,1 };
	#pragma endregion

	#pragma region BunnyMesh / Transform
	if (m_bunnyMesh.load("./stanford/bunny.obj") == false)
	{
		printf("Bunny mesh error!\n");
		return false;
	}
	m_bunnyTransform = {
		0.1f ,0    ,0    ,0 ,
		0    ,0.1f ,0    ,0 ,
		0    ,0    ,0.1f ,0 ,
		0    ,0    ,0    ,1
	};
	#pragma endregion

	#pragma region SpearMesg / Transform
	if (m_spearMesh.load("./soulspear/soulspear.obj", true, true) == false)
	{
		printf("SoulSpear Mesh Error!\n");
		return false;
	}
	m_spearTransform = {
		1  ,0  ,0  ,0,
		0  ,1  ,0  ,0,
		0  ,0  ,1  ,0,
		0  ,0  ,0  ,1 };
	#pragma endregion

	#pragma region Pokemon / Transform
	if (m_pokemonMesh.load("./rol/Riolu.obj", true, true) == false)
	{
		printf("Pokemon Mesh Error!\n");
		return false;
	}
	m_pokemonTransform = {
		2  ,0  ,0  ,0,
		0  ,2  ,0  ,0,
		0  ,0  ,2  ,0,
		2.5f ,0 ,2.5f  ,1 };
	#pragma endregion

	for (int i = 0; i < 10; i++)
		m_scene->AddInstance(new Instance(glm::vec3(i * 2, 0, 0), glm::vec3(0, i * 30, 0), glm::vec3(1, 1, 1), &m_spearMesh, &m_normalMapShader));

	m_scene->AddInstance(new Instance(m_pokemonTransform, &m_pokemonMesh, &m_normalMapShader));
	//m_scene->AddInstance(new Instance(m_bunnyTransform, &m_bunnyMesh, &m_phongShader));

	return true;
#pragma endregion
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