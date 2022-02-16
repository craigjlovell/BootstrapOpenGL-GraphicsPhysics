#pragma once
#include "PhysicsScene.h"

class Softbody
{
public:

	Softbody();
	~Softbody();

	static void Build(PhysicsScene* a_scene, glm::vec2 s_position, float s_spacing, float s_springForce, float a_damping, std::vector<std::string>& a_strings);
protected:
};
