#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include "Circle.h"
#include "Plane.h"

#include <list>
#include <iostream>

PhysicsScene::PhysicsScene() : m_timeStep(0.01f), m_gravity(glm::vec2(0, 0))
{

}

PhysicsScene::~PhysicsScene()
{
	for (auto pActor : m_actors)
	{
		delete pActor;
	}
}

void PhysicsScene::AddActor(PhysicsObject* a_actor)
{
	m_actors.push_back(a_actor);
}

void PhysicsScene::RemoveActor(PhysicsObject* a_actor)
{
	auto it = std::find(m_actors.begin(), m_actors.end(), a_actor);
	if (it != m_actors.end())
	{
		m_actors.erase(it);
	}
}

void PhysicsScene::Update(float a_dt)
{	
	// Update physics Objects
	static float accumulatedTime = 0.0f;
	accumulatedTime += a_dt;

	while (accumulatedTime >= m_timeStep)
	{
		for (auto pActor : m_actors)
		{
			pActor->FixedUpdate(m_gravity, m_timeStep);
		}
		
		accumulatedTime -= m_timeStep;

		CheckForCollisions();
	}

}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors) pActor->MakeGizmo();
	
}
//=====================================================================================================================================================
//Function Pointer array for handling our collisions 
typedef bool (*fn)(PhysicsObject*, PhysicsObject*);
static fn collisionFunctionArray[] =
{
	PhysicsScene::Plane2Plane,	PhysicsScene::Plane2Circle,		PhysicsScene::Plane2Box,
	PhysicsScene::Circle2Plane, PhysicsScene::Circle2Circle,	PhysicsScene::Circle2Box,
	PhysicsScene::Box2Plane,	PhysicsScene::Box2Circle,		PhysicsScene::Box2Box,
};

void PhysicsScene::CheckForCollisions()
{
	int actorCount = m_actors.size();

	//we need to check our collisions agenst all other objects expect this one.......

	for (int outer = 0; outer < actorCount - 1; outer++)
	{
		for (int inner = outer + 1; inner < actorCount; inner++)
		{
			PhysicsObject* object1 = m_actors[outer];
			PhysicsObject* object2 = m_actors[inner];
			int shapeID1 = object1->GetShapeID();
			int shapeID2 = object2->GetShapeID();

			// using the function pointer
			int functionIDX = (shapeID1 * SHAPE_COUNT) + shapeID2;
			fn collisionFunctionPTR = collisionFunctionArray[functionIDX];
			if (collisionFunctionPTR != nullptr)
			{
				//check if a collision occurs ....
				collisionFunctionPTR(object1, object2);
			}
		}
	}
}

bool PhysicsScene::Plane2Plane(PhysicsObject* a_plane, PhysicsObject* a_otherPlane)
{
	return false;
}

bool PhysicsScene::Plane2Circle(PhysicsObject* a_plane, PhysicsObject* a_circle)
{
	return Circle2Plane(a_circle, a_plane);
}

bool PhysicsScene::Plane2Box(PhysicsObject* a_plane, PhysicsObject* a_box)
{
	return false;
}

bool PhysicsScene::Circle2Plane(PhysicsObject* a_circle, PhysicsObject* a_plane)
{
	Circle* circle = dynamic_cast<Circle*>(a_circle);
	Plane* plane = dynamic_cast<Plane*>(a_plane);

	//if tghis is successful then test for a collision....

	if (circle != nullptr && plane != nullptr)
	{
		glm::vec2 collisionNormal = plane->GetNormal();
		float circleToPlane = glm::dot(circle->GetPosition(), plane->GetNormal()) - plane->GetDistance();
		float intersection = circle->GetRadius() - circleToPlane;
		float velocityOutOfThePlane = glm::dot(circle->GetVelocity(), plane->GetNormal());
		if (intersection > 0 && velocityOutOfThePlane < 0)
		{
			// we can set objects to respond to a plane collision.
			glm::vec2 contact = circle->GetPosition() + (collisionNormal * -circle->GetRadius());
			plane->ResolvePlaneCollision(circle, contact);
			
			return true;
		}
	}
	return false;
}

bool PhysicsScene::Circle2Circle(PhysicsObject* a_circle, PhysicsObject* a_otherCircle)
{
	//tried to cast object to circle to circle
	Circle* circle1 = dynamic_cast<Circle*>(a_circle);
	Circle* circle2 = dynamic_cast<Circle*>(a_otherCircle);

	//if successful then test for collision
	if (circle1 != nullptr && circle2 != nullptr)
	{
		// Do the math to check for overlap
		float dist = glm::distance(circle1->GetPosition(), circle2->GetPosition());
		// ... if the circle touch, resolve the collision
		float penetration = circle1->GetRadius() + circle2->GetRadius() - dist;

		if (penetration > 0)
		{
			circle1->ResolveCollision(circle2, .5f * (circle1->GetPosition() + circle2->GetPosition()));
			return true;
		}
	}

	return false;
}

bool PhysicsScene::Circle2Box(PhysicsObject* a_circle, PhysicsObject* a_box)
{
	return false;
}

bool PhysicsScene::Box2Plane(PhysicsObject* a_box, PhysicsObject* a_plane)
{
	return false;
}

bool PhysicsScene::Box2Circle(PhysicsObject* a_box, PhysicsObject* a_circle)
{
	return false;
}

bool PhysicsScene::Box2Box(PhysicsObject* a_box, PhysicsObject* a_otherBox)
{
	return false;
}



