#include "Scene.h"
#include "Instance.h"

Scene::Scene(Camera* a_camera, glm::vec2 a_windowSizem, Light& a_light, glm::vec3 a_ambientLight) :
	m_camera(a_camera), m_windowSize(a_windowSizem), m_globalDirLight(a_light), m_ambientLight(a_ambientLight)
{

}

Scene::~Scene()
{
	for (auto it = m_instances.begin(); it != m_instances.end(); it++)
	{
		delete(*it);
	}
	
}

void Scene::AddInstance(Instance* a_instance)
{
	m_instances.push_back(a_instance);
}

void Scene::Draw()
{
	for (int i = 0; i < MAX_LIGHTS && i < GetNumLights(); i++)
	{
		m_pointLightPositions[i] = m_pointLights[i].direction;
		m_pointLightColors[i] = m_pointLights[i].color;
	}

	for (auto it = m_instances.begin(); it != m_instances.end(); it++)
	{
		Instance* instance = *it;
		instance->Draw(this);
	}
}