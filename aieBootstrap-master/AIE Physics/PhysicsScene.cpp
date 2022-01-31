#include "PhysicsScene.h"
#include "PhysicsObject.h"
#include "Rigidbody.h"
#include "Circle.h"

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

	// Must remove later =================
	static std::list<PhysicsObject*> dirty;

	// ======================

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

		// Must remove later =================
		// Check for collision we will need to update this to have some kind of scene managment 
		for (auto pActor : m_actors)
		{
			for(auto pOther : m_actors)
			{
				if (pActor == pOther)
					continue;

				if (std::find(dirty.begin(), dirty.end(), pActor) != dirty.end() &&
					std::find(dirty.begin(), dirty.end(), pOther) != dirty.end())
					continue;

				Rigidbody* pRigid = dynamic_cast<Rigidbody*>(pActor);
				if (pRigid->CheckCollision(pOther))
				{
					pRigid->ApplyForceToActor(dynamic_cast<Rigidbody*>(pOther), 
						pRigid->GetVelocity() * pRigid->GetMass());
					dirty.push_back(pRigid);
					dirty.push_back(pOther);
				}
			}
			dirty.clear();
		}
		
		// ================================

	}

}

void PhysicsScene::Draw()
{
	for (auto pActor : m_actors)
	{
		pActor->Draw();
	}
}

bool PhysicsScene::Circle2Circle(PhysicsObject* a_circle, PhysicsObject* a_otherCircle)
{
	//tried to cast object to circle to circle
	Circle* circle1 = dynamic_cast<Circle*>(a_circle);
	Circle* circle2 = dynamic_cast<Circle*>(a_otherCircle);

	//if successful then test for collision
	if (circle1 != nullptr && circle2 != nullptr)
	{
		//TODO math
	}

	return false;
}
