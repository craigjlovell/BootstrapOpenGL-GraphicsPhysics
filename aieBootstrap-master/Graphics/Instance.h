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

	static glm::mat4 MakeTransform(glm::vec3 a_position, glm::vec3 a_eulerAngles, glm::vec3 a_scale);
	glm::mat4& GetTransform() { return m_transform; }
	void SetTransform(glm::mat4 a_transform) { m_transform = a_transform; }

	void SetRotation(float a_eulerAngles);
	
	glm::vec3 GetScale() { return m_scale; }
	void SetScale(glm::vec3 a_scale) { m_transform *= glm::scale(m_transform, a_scale); }
	void SetSize(glm::vec3 a_eulerAngles);


	glm::vec3 GetRotation() { return m_rotation; }
	
protected:
	glm::vec3 m_rotation;
	glm::vec3 m_scale;
	glm::mat4 m_transform;
	aie::OBJMesh* m_mesh;
	aie::ShaderProgram* m_shader;

};

