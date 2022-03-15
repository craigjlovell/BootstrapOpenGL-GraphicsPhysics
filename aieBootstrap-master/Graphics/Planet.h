#pragma once
#include "glm/glm.hpp"
class Planet
{
public:

	Planet(glm::vec3 a_position, float a_size, glm::vec4 a_color, glm::vec3 a_rotation);
	~Planet();

	void Update();
	void CreatePlanet();

	//void SetRotation();
	//void GetRotation();
	//
	//void SetPosition();
	//void GetPosition();


	glm::vec4 GetColour() { return m_colour; }

protected:

	glm::vec3 m_position;
	float m_size;
	glm::vec4 m_colour;
	glm::vec3 m_rotation;

private:

};

