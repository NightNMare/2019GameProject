#pragma once
#include "Collider.h"
class TriangleCollider :
	public Collider
{
public:
	TriangleCollider(Transform& transform, const Vector2& top, const Vector2& left, const Vector2& right);

public:
	Triangle boundingTriangle;
public:
	virtual bool Intersected(Collider& col);
	virtual bool Intersected(const AABBBox& box);
	virtual bool Intersected(const Circle& circle);
	virtual bool Intersected(const Vector2& vector);
	virtual bool Intersected(const Triangle& tri);

public:
	Triangle GetTransformedTriangle();

	virtual void Update() {}
};

