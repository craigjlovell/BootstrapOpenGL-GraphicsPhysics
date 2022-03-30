#pragma once
#include "glm/glm.hpp"
#include <list>
#include <vector>

class Camera;
class FlyCamera;
class Instance;

const int MAX_LIGHTS = 4;

struct Light
{
	Light() {}
	Light(glm::vec3 dir, glm::vec3 col, float intensity)
	{
		direction = dir;
		color = col * intensity;
	}

	glm::vec3 direction;
	glm::vec3 color;
};

class Scene
{
public:

	Scene(Camera* a_camera, glm::vec2 a_windowSizem, Light& a_light, glm::vec3 a_ambientLight);
	~Scene();

	void AddInstance(Instance* a_instance);
	void Draw();

	Camera*					GetCamera()				{ return m_camera; }
	glm::vec2				GetWindowSize()			{ return m_windowSize; }
	Light&					GetGlobalLight()		{ return m_globalDirLight; }
	glm::vec3				GetAmibentLight()		{ return m_ambientLight; }
	std::vector<Light>&		GetPointLights()		{ return m_pointLights; }
	int						GetNumLights()			{ return (int)m_pointLights.size(); }
	std::list<Instance*>	GetInstances()			{ return m_instances; }

	glm::vec3*		GetPointLightPositions()	{ return &m_pointLightPositions[0]; }
	glm::vec3*		GetPointLightColors()		{ return &m_pointLightColors[0]; }

	void			SetPointLights(Light a_light) { m_pointLights.push_back(a_light); }
	void			AddPointLights(glm::vec3 a_direction, glm::vec3 a_color, float a_intensity) 
					{ m_pointLights.push_back(Light(a_direction, a_color, a_intensity)); }

protected:

	Camera* m_camera;
	glm::vec2 m_windowSize;

	Light m_globalDirLight;
	glm::vec3 m_ambientLight;
	std::vector <Light> m_pointLights;
	std::list<Instance*> m_instances;

	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColors[MAX_LIGHTS];

};

