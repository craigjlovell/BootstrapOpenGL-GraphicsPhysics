#pragma once
#include <vector>
#include <glm/glm.hpp>

class PhysicsObject;
class Circle;

class PhysicsScene
{
public:

	PhysicsScene();
	~PhysicsScene();

	void AddActor(PhysicsObject* a_actor);
	void RemoveActor(PhysicsObject* a_actor);

	// will update physics simulatioin calls update of each actor and updates
	// this will handle colision detection
	void Update(float a_dt);

	// This is called once per frame and handles the rendering of physical objects
	// this will let you draw a variaty of objects using gizmo class and add them to loop
	void Draw();

	void SetGravity(const glm::vec2 a_gravity) {m_gravity = a_gravity;}
	glm::vec2 GetGravity() const { return m_gravity; }

	void SetTimeStep(const float a_timeStep) { m_timeStep = a_timeStep; }
	float GetTimeStep() const { return m_timeStep; }

	static bool Circle2Circle(PhysicsObject* a_circle, PhysicsObject* a_otherCircle);

protected:

	glm::vec2 m_gravity;
	float m_timeStep;

	// Stores all the physics objects in the scene as well as functions that
	// will add and or remove objects
	std::vector<PhysicsObject*> m_actors;


private:

};