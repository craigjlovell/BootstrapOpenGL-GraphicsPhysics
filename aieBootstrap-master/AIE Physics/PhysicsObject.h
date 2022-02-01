#pragma once

#include <glm/glm.hpp>

// Abstract class
enum ShapeType
{
	PLANE = 0,
	CIRCLE,
	BOX,
	SHAPE_COUNT
};


class PhysicsObject
{
protected:

	PhysicsObject(ShapeType a_shapeID) : m_shapeID(a_shapeID) {}

public:

	virtual void FixedUpdate(glm::vec2 a_gravity, float a_timeStep) = 0;
	virtual void MakeGizmo() = 0;
	virtual void ResetPos() {};

	ShapeType GetShapeID() { return m_shapeID; }

protected:

	ShapeType m_shapeID;

private:

};