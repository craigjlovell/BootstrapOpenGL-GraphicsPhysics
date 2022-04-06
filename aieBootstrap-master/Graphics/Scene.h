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

	void Update(float deltaTime);

	Camera*					GetCamera()					{ return m_camera; }
	void					SetCamera(Camera* a_cam)	{ m_camera = a_cam; }

	glm::vec2				GetWindowSize()				{ return m_windowSize; }
	Light&					GetGlobalLight()			{ return m_globalDirLight; }
	glm::vec3				GetAmibentLight()			{ return m_ambientLight; }
	std::vector<Light>&		GetPointLights()			{ return m_pointLights; }
	int						GetNumLights()				{ return (int)m_pointLights.size(); }

	float					GetScreenTime()				{ return m_sceneRunTime; }

	int						GetCamCount()				{ return m_camCount; }
	int						GetCamIndex()				{ return m_camIndex; }
	Camera*					GetCamIndexPoint(int a_index) { return m_cameras[a_index]; }

	std::list<Instance*>&	GetInstances()				{ return m_instances; }
	void					SetInstances(std::list<Instance*> a_inst) { m_instances = a_inst; }

	glm::vec3*				GetPointLightPositions()	{ return &m_pointLightPositions[0]; }
	glm::vec3*				GetPointLightColors()		{ return &m_pointLightColors[0]; }

	void			SetPointLights(Light a_light) { m_pointLights.push_back(a_light); }
	void			AddPointLights(glm::vec3 a_direction, glm::vec3 a_color, float a_intensity) 
					{ m_pointLights.push_back(Light(a_direction, a_color, a_intensity)); }

protected:

	Camera* m_camera;
	Camera** m_cameras;
	glm::vec2 m_windowSize;

	Light m_globalDirLight;
	glm::vec3 m_ambientLight;
	std::vector <Light> m_pointLights;
	std::list<Instance*> m_instances;

	glm::vec3 m_pointLightPositions[MAX_LIGHTS];
	glm::vec3 m_pointLightColors[MAX_LIGHTS];

	float m_sceneRunTime = 0;

	int m_camIndex;
	int m_camCount;

};

