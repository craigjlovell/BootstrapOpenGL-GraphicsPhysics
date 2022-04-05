#pragma once
#include "glm/glm.hpp"
#include "glm/ext.hpp"



class Camera;
struct Light;
class Scene;

namespace aie
{
	class OBJMesh;
	class ShaderProgram;
}
class Instance
{
public:

	Instance(glm::mat4 a_transform, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader);
	Instance(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale, aie::OBJMesh* a_mesh, aie::ShaderProgram* a_shader);

	void Draw(Scene* a_scene);

	glm::mat4 MakeTransform(glm::vec3 a_position, glm::vec3 a_rotation, glm::vec3 a_scale);
	glm::mat4 GetTransform() { return m_transform; /*return MakeTransform(m_position, m_rotation, m_scale);*/ }
	void SetTransform(glm::mat4 a_transform) { m_transform = a_transform; }

	//glm::vec3 GetRotation() { glm::quat quat = glm::quat_cast(m_transform); return glm::vec3(glm::degrees(glm::pitch(quat)), glm::degrees(glm::yaw(quat)), glm::degrees(glm::roll(quat))); }
	//void SetRotation(glm::vec3 a_rotation) { m_transform = 
	//	glm::rotate(glm::mat4(1), glm::radians(a_rotation.x), glm::vec3(1, 0, 0)) *
	//	glm::rotate(glm::mat4(1), glm::radians(a_rotation.y), glm::vec3(0, 1, 0)) *
	//	glm::rotate(glm::mat4(1), glm::radians(a_rotation.z), glm::vec3(0, 0, 1)); }
	void SetRotation(glm::vec3 a_rotation) { m_rotation = a_rotation; }
	glm::vec3 GetRotation() { return m_rotation; }

	glm::vec3 GetScale() { return glm::vec3(
		glm::length(glm::vec3(m_transform[0][0], m_transform[1][0], m_transform[2][0])), 
		glm::length(glm::vec3(m_transform[0][1], m_transform[1][1], m_transform[2][1])), 
		glm::length(glm::vec3(m_transform[0][2], m_transform[1][2], m_transform[2][2]))); }
	void SetScale(glm::vec3 a_scale) { m_transform = glm::scale(glm::mat4(1), a_scale); }
	
	glm::vec3 GetPosition() { return m_transform[3]; }
	void SetPosition(glm::vec3 a_position) { m_transform[3].x = a_position.x, m_transform[3].y = a_position.y, m_transform[3].z = a_position.z ; }

protected:
	glm::vec3 m_rotation;
	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;

private:

	glm::mat4 m_transform;
};

