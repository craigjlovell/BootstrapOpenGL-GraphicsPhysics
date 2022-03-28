#pragma once
#include "glm/glm.hpp"


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

	static glm::mat4 MakeTransform(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale);
	void SetRotation(float a_eulerAngles);
	glm::mat4 Rotation(glm::mat4 matrix, char axis, float rotationAmount);
	void SetTransform(glm::mat4 a_transform) { m_transform = a_transform; }
	glm::mat4& GetTransform() { return m_transform;  }

	glm::vec3 GetRotation() { return m_rotation; }

	glm::vec3 GetScale();

	glm::vec3 GetPosition();

	
protected:
	glm::vec3 m_rotation;
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;

};

