#pragma once
#include <vector>
#include <glm/glm.hpp>

class PhysicsObject;

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

	void CheckForCollisions();


	static bool Plane2Plane(PhysicsObject* a_plane, PhysicsObject* a_otherPlane);
	static bool Plane2Circle(PhysicsObject* a_plane, PhysicsObject* a_circle);
	static bool Plane2Box(PhysicsObject* a_plane, PhysicsObject* a_box);
	//static bool Plane2Player(PhysicsObject* a_plane, PhysicsObject* a_player);

	static bool Circle2Plane(PhysicsObject* a_circle, PhysicsObject* a_plane);
	static bool Circle2Circle(PhysicsObject* a_circle, PhysicsObject* a_otherCircle);
	static bool Circle2Box(PhysicsObject* a_circle, PhysicsObject* a_box);
	//static bool Circle2Player(PhysicsObject* a_circle, PhysicsObject* a_player);
		
	static bool Box2Plane(PhysicsObject* a_box, PhysicsObject* a_plane);	
	static bool Box2Circle(PhysicsObject* a_box, PhysicsObject* a_circle);
	static bool Box2Box(PhysicsObject* a_box, PhysicsObject* a_otherBox);
	//static bool Box2Player(PhysicsObject* a_box, PhysicsObject* a_player);
	//
	//static bool Player2Plane(PhysicsObject* a_player, PhysicsObject* a_plane);
	//static bool Player2Circle(PhysicsObject* a_player, PhysicsObject* a_circle);
	//static bool Player2Box(PhysicsObject* a_player, PhysicsObject* a_box);
	//static bool Player2Player(PhysicsObject* a_player, PhysicsObject* a_otherPlayer);

protected:

	glm::vec2 m_gravity;
	float m_timeStep;

	// Stores all the physics objects in the scene as well as functions that
	// will add and or remove objects
	std::vector<PhysicsObject*> m_actors;


private:

};