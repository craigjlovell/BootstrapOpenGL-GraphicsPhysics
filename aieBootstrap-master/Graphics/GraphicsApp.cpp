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

GraphicsApp::~GraphicsApp() 
{

}

bool GraphicsApp::startup()
{
	setBackgroundColour(0.25f, 0.25f, 0.25f);

	// initialise gizmo primitive counts
	Gizmos::create(10000, 10000, 10000, 10000);

	// create simple camera transforms
	m_viewMatrix = glm::lookAt(vec3(10), vec3(0), vec3(0, 1, 0));
	m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, 16.0f / 9.0f, 0.1f, 1000.0f);

	m_camera = new Camera();
	m_flyCamera = new FlyCamera();

	// Default Light Values
	Light light;
	light.direction = { 1, -1, 1 };
	light.color = { 1, 1, 1 };
	m_ambientLight = { 0.5f, 0.5f, 0.5f };

	m_emitter = new ParticleEmitter();
	m_emitter->Initialise(
		1000, 500,
		0.1f, 1.0f,
		1.0f, 5.0f,
		1.0f, 0.1f,
		glm::vec4(1, 0, 0, 1),
		glm::vec4(1, 1, 0, 1));

	t_position = { 0, 0, 0 };
	t_rotation = { 0, 0, 0 };
	t_scale	   = { 1, 1, 1 };

	t_position2 = { 0, 0, 0 };
	t_rotation2 = { 0, 0, 0 };
	t_scale2 = { 1, 1, 1 };

	m_scene = new Scene(m_flyCamera, glm::vec2(getWindowWidth(), getWindowHeight()), light, m_ambientLight);

	//scale = { .5f ,.5f ,.5f };

	m_scene->AddPointLights(glm::vec3(5, 3, 0), glm::vec3(1, 0, 0), 25);
	m_scene->AddPointLights(glm::vec3(-5, 3, 0), glm::vec3(0, 0, 1), 50);

	//m_stationaryCamera = StationaryCamera(glm::vec3{ -10,2,0 }, m_camera.GetRotation());

	return LaunchSahders();
}

void GraphicsApp::shutdown() 
{
	Gizmos::destroy();
	delete m_scene;
}

void GraphicsApp::update(float deltaTime) 
{
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

	ImGui::Begin("particles Settings");
	ImGui::DragFloat3("particles pos", &m_emitter->m_position[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles rate", &m_emitter->m_emitRate, 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles timer", &m_emitter->m_emitTimer, 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles lifemin", &m_emitter->m_lifespanMin, 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles lifemax", &m_emitter->m_lifespanMax, 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles start color", &m_emitter->m_startColor[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles end color", &m_emitter->m_endColor[0], 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles start size", &m_emitter->m_startSize, 0.1f, -1.0f, 1.0f);
	ImGui::DragFloat3("particles end size", &m_emitter->m_endSize, 0.1f, -1.0f, 1.0f);
	ImGui::Checkbox("particles IsDraw", &m_emitter->isDraw);
	ImGui::End();

	
	//ImGui::Begin("Object Local Transform");
	//ImGui::DragFloat3("Position", (float *) (&m_raygunIns->GetTransform()[3]), 0.1f, -20.0f, 20.0f); 
	//
	//glm::vec3 change = {0,0,0};
	//ImGui::DragFloat3("Rotation", &change[0], 0.1f, -20.0f, 20.0f);
	//m_raygunIns->SetRotation(change.y, change.x, change.z);
	//
	//glm::vec3 scale = m_raygunIns->GetScale();
	//ImGui::DragFloat3("Scale", &scale[0], 0.1f, -20.0f, 20.0f);
	//m_raygunIns->SetSize(scale, scale, scale);
	//
	//ImGui::End();

	auto* obj = m_scene->GetInstances().back();
	ImGui::Begin("Raygun Local Transform");
	ImGui::DragFloat3("Position", &t_position[0], 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat3("Rotation", &t_rotation[0], 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat3("scale", &t_scale[0], 0.1f, -1.0f, 20.0f);
	ImGui::End();
	obj->SetTransform(obj->MakeTransform(t_position, t_rotation, t_scale));

	auto* obj2 = m_scene->GetInstances().front();
	ImGui::Begin("Spear Local Transform");
	ImGui::DragFloat3("Position", &t_position2[0], 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat3("Rotation", &t_rotation2[0], 0.1f, -20.0f, 20.0f);
	ImGui::DragFloat3("scale", &t_scale2[0], 0.1f, -1.0f, 20.0f);
	ImGui::End();
	obj2->SetTransform(obj2->MakeTransform(t_position2, t_rotation2, t_scale2));

	ImGui::Begin("Bunny Local Transform");
	ImGui::DragFloat("Position", (float*) &m_bunnyTransform[3], 0.1f, -20.0f, 20.0f);
	ImGui::End();


	// Run Camera Update
	m_camera->update(deltaTime);
	m_flyCamera->SetSpeed();
	m_flyCamera->update(deltaTime);

	if(m_emitter->isDraw == true)
		m_emitter->Update(deltaTime, m_flyCamera->GetTransform(m_flyCamera->GetPosition(), glm::vec3(0), glm::vec3(1)));

	// quit if we press escape
	aie::Input* input = aie::Input::getInstance();

	if (input->isKeyDown(aie::INPUT_KEY_ESCAPE))
		quit();
	
	if (input->isKeyDown(aie::INPUT_KEY_RIGHT))
		m_bunnyTransform = Rotation(m_bunnyTransform, 'y', -0.8f);
	if (input->isKeyDown(aie::INPUT_KEY_LEFT))
		m_bunnyTransform = Rotation(m_bunnyTransform, 'y', 0.8f);
}

void GraphicsApp::draw() 
{
	// We nered to bind our rendertarget first
	m_renderTarget.bind();

	// wipe the screen to the background colour
	clearScreen();

	// update perspective based on screen size
	//m_projectionMatrix = glm::perspective(glm::pi<float>() * 0.25f, getWindowWidth() / (float)getWindowHeight(), 0.1f, 1000.0f);
	glm::mat4 projectionMatrix = m_flyCamera->GetProjectionMatrix((float)getWindowWidth(), (float)getWindowHeight());
	glm::mat4 viewMatrix = m_flyCamera->GetViewMatrix();
	auto pvm = projectionMatrix * viewMatrix * glm::mat4(1);

	m_scene->Draw();

#pragma region Bunny
	m_phongExtShader.bind();
	m_phongExtShader.bindUniform("LightDirection", m_scene->GetGlobalLight().direction);
	m_phongExtShader.bindUniform("AmbientColor", m_scene->GetAmibentLight());
	m_phongExtShader.bindUniform("LightColor", m_scene->GetGlobalLight().color);
	m_phongExtShader.bindUniform("CameraPosition", m_flyCamera->GetPosition());

	pvm = projectionMatrix * viewMatrix * m_bunnyTransform;
	m_phongExtShader.bindUniform("ProjectionViewModel", pvm);
	m_phongExtShader.bindUniform("ModelMatrix", m_bunnyTransform);

	m_marbleTexture.bind(0);
	m_phongExtShader.bindUniform("seamlessTexture", 0);

	m_hatchingTexture.bind(1);
	m_phongExtShader.bindUniform("hatchingTexture", 1);

	m_rampTexture.bind(2);
	m_phongExtShader.bindUniform("rampTexture", 2);

	m_bunnyMesh.draw();
#pragma endregion

	m_particleShader.bind();
	pvm = projectionMatrix * viewMatrix * m_particleTransform;
	m_particleShader.bindUniform("ProjectionViewModel", pvm);
	if (m_emitter->isDraw == true)
		m_emitter->Draw();
	
	m_shader.bind();
	pvm = projectionMatrix * viewMatrix * m_hexTransform;
	m_shader.bindUniform("ProjectionViewModel", pvm);
	m_hexMesh.draw();

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

	// Unbind the target to return it to the back bufffer
	m_renderTarget.unbind();
	clearScreen();

	// Bind the post processing shader and texture
	m_advancePostShader.bind();
	m_advancePostShader.bindUniform("colorTarget", 0);
	m_advancePostShader.bindUniform("postProcessTarget", m_postProcessEffect);
	m_advancePostShader.bindUniform("screensize", glm::vec2(getWindowWidth(), getWindowHeight()));
	m_advancePostShader.bindUniform("deltaTime", m_dt);
	m_advancePostShader.bindUniform("outOfColorTarget", 1);
	m_advancePostShader.bindUniform("positionTexture", 0);
	m_advancePostShader.bindUniform("mouseFocusPoint", glm::vec2(0,0));
	m_renderTarget.getTarget(0).bind(0);

	m_screenQuad.draw();
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

bool GraphicsApp::LaunchSahders()
{
#pragma region LaunchShaders

	#pragma region RenderTarget
	if (m_renderTarget.initialise(1, getWindowWidth(), getWindowHeight()) == false)
	{
		printf("Render Target Error!\n");
		return false;
	}
	#pragma endregion

	#pragma region Shader
	m_shader.loadShader(aie::eShaderStage::VERTEX, "./shaders/simple.vert");
	m_shader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/simple.frag");
	if (m_shader.link() == false)
	{
		printf("Simple Shader Error: %s\n", m_shader.getLastError());
		return false;
	}
	#pragma endregion

	#pragma region PhongExtShader
	m_phongExtShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/phongExt.vert");
	m_phongExtShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/phongExt.frag");
	if (m_phongExtShader.link() == false)
	{
		printf("PhongExt Shader Error: %s\n", m_phongExtShader.getLastError());
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

	#pragma region PostShader
	m_postShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/post.vert");
	m_postShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/post.frag");
	if (m_postShader.link() == false)
	{
		printf("Post-Porcessing Shader Error: %s\n", m_postShader.getLastError());
		return false;
	}
	#pragma endregion

	#pragma region AdvancePostShader
	m_advancePostShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/advancePost.vert");
	m_advancePostShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/advancePost.frag");
	if (m_advancePostShader.link() == false)
	{
		printf("Post-Porcessing Shader Error: %s\n", m_advancePostShader.getLastError());
		return false;
	}
	#pragma endregion

	#pragma region Particle Shader
	m_particleShader.loadShader(aie::eShaderStage::VERTEX, "./shaders/particle.vert");
	m_particleShader.loadShader(aie::eShaderStage::FRAGMENT, "./shaders/particle.frag");
	if (m_particleShader.link() == false)
	{
		printf("Particle Shader Error: %s\n", m_particleShader.getLastError());
		return false;
	}
	#pragma endregion

	// CREATE THE FULLSCREEN QUAD FOR POST PROCESSING EFFECTS
	m_screenQuad.InitialiseFullScreenQuad();

	Mesh::Vertex verticies[4];
	verticies[0].position = { -0.5 ,0 ,  0.5 ,1 };
	verticies[1].position = {  0.5 ,0 ,  0.5 ,1 };
	verticies[2].position = { -0.5 ,0 , -0.5 ,1 };
	verticies[3].position = {  0.5 ,0 , -0.5 ,1 };

	unsigned int indicies[6] = { 0, 1, 2, 2, 1, 3 };

	#pragma region Quad Mesh / Transform
	// This needs to be commented to have hex box gird work
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
		-4    ,0    ,4    ,1
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

	#pragma region Raygun / Transform
	if (m_raygunMesh.load("./raygun/Raygun_low.obj", true, true) == false)
	{
		printf("Raygun Mesh Error!\n");
		return false;
	}
	m_raygunTransform = {
		0.5f  ,0  ,0  ,0,
		0  ,0.5f  ,0  ,0,
		0  ,0  ,0.5f  ,0,
		0 ,0 ,0 ,1 };
	
	#pragma endregion

	m_particleTransform = {
		1  ,0  ,0  ,0,
		0  ,1  ,0  ,0,
		0  ,0  ,1  ,0,
		4  ,0  ,0  ,1 };

	m_marbleTexture.load("./textures/marble2.jpg");
	m_hatchingTexture.load("./textures/Ramp02.png");
	m_rampTexture.load("./textures/ramps.png", true);
	
	//for (int i = 0; i < 10; i++)
	//	m_scene->AddInstance(new Instance(glm::vec3(i * 2, 0, 0), glm::vec3(0, i * 30, 0), glm::vec3(1, 1, 1), &m_spearMesh, &m_normalMapShader));
	m_raygunIns = new Instance(m_raygunTransform, &m_raygunMesh, &m_normalMapShader);
	m_scene->AddInstance(new Instance(m_spearTransform, &m_spearMesh, &m_normalMapShader));
	m_scene->AddInstance(m_raygunIns);

	//m_scene->AddInstance(new Instance(m_bunnyTransform, &m_bunnyMesh, &m_phongShader));

	//CreateHex();
	//CreateBox();
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

	m_cubeMesh.Initialise(8, verticies, 36, indicies);

	m_cubeTransform = {
		10  ,0  ,0  ,0,
		0  ,10  ,0  ,0,
		0  ,0  ,10  ,0,
		0  ,0  ,0  ,1 };
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

	m_pyMesh.Initialise(5, verticies, 18, indicies);
	m_pyTransform = {
		10  ,0  ,0  ,0,
		0  ,10  ,0  ,0,
		0  ,0  ,10  ,0,
		0  ,0  ,0  ,1 };
}

void GraphicsApp::CreateHex()
{
	Mesh::Vertex verticies[7];
	verticies[0].position = { 0, 0.0f, 0, 1};
	verticies[1].position = { -0.5f, 0.0f, -1.0f, 1};
	verticies[2].position = { 0.5f, 0.0f, -1.0f,1   };
	verticies[3].position = { 1.0f, 0.0f, 0.0f,1   };
	verticies[4].position = { 0.5f, 0.0f, 1.0f,1  };
	verticies[5].position = { -0.5f, 0.0f, 1.0f,1};
	verticies[6].position = { -1.0f, 0.0f, 0.0f, 1};

	unsigned int indicies[18] = {
								 1,6,0,
								 6,5,0,
								 5,4,0,
								 4,3,0,
								 3,2,0,
								 2,1,0};

	m_hexMesh.Initialise(7, verticies, 18, indicies);
	m_hexTransform = {
		10  ,0  ,0  ,0,
		0  ,10  ,0  ,0,
		0  ,0  ,10  ,0,
		0  ,0  ,0  ,1 };
}

void GraphicsApp::CreateGrid()
{
	for (int row = 0; row < 5; row++)
	{
		for (int col = 0; col < 5; col++)
		{
			
		}
	}

}
