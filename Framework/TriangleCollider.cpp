#include "stdafx.h"
#include "TriangleCollider.h"
#include "Collision.h"

TriangleCollider::TriangleCollider(Transform& transform, const Vector2& top, const Vector2& left, const Vector2& right)
	: Collider(transform), boundingTriangle(top, left, right)
{

}

bool TriangleCollider::Intersected(Collider& col) {
	return col.Intersected(GetTransformedTriangle());
}

bool TriangleCollider::Intersected(const AABBBox& box) {
	return Collision::Intersected(GetTransformedTriangle(), box);
}

bool TriangleCollider::Intersected(const Circle& circle) {
	return Collision::Intersected(circle, GetTransformedTriangle());
}

bool TriangleCollider::Intersected(const Vector2& vector) {
	return 0;
}

bool TriangleCollider::Intersected(const Triangle& tri) {
	return 0;
}

Collider::Triangle TriangleCollider::GetTransformedTriangle() {
	Vector2 top, left, right;
	top.SetVector(transform.position + boundingTriangle.top);
	left.SetVector(transform.position + boundingTriangle.left);
	right.SetVector(transform.position + boundingTriangle.right);
	return Triangle(top, left, right);
}
