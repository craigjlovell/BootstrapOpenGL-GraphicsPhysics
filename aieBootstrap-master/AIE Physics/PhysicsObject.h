#pragma once

#include <glm/glm.hpp>

// Abstract class
enum ShapeType
{
	PLANE = 0,
	CIRCLE,
	BOX,
	//PLAYER,
	SHAPE_COUNT
};


class PhysicsObject
{
protected:

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:

	void Update();
	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep) = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPos() {};
	void Debug();

	ShapeType GetShapeID() { return m_shapeID; }

	float GetElasticity() { return m_elasticity; }
	void SetElasticity(float a_elsticity) { m_elasticity = a_elsticity; }

protected:

	ShapeType m_shapeID;
	float m_elasticity;
	bool m_isKinematic;

private:

};