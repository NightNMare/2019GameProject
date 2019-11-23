#pragma once
#include "AABBCollider.h"
#include "CircleCollider.h"
#include "TriangleCollider.h"
#include <utility>

//�浹�� ó���� �Լ��� �����Դϴ�.
//Collider�� ��� ���Ƿ� �浹 ����� �����մϴ�.
typedef std::pair<int, int> P;

namespace Collision
{
	bool Intersected(const Collider::AABBBox& a, const Collider::AABBBox& b);
	bool Intersected(const Collider::AABBBox& a, const Collider::Circle& b);
	bool Intersected(const Collider::Circle& a, const Collider::Circle& b);
	bool Intersected(const Collider::AABBBox& a, const Vector2& b);
	bool Intersected(const Collider::Circle& a, const Vector2& b);
	bool Intersected(const Collider::Circle& a, const Collider::Triangle& b);
	bool Intersected(const Collider::Triangle& a, const Collider::AABBBox& b);
	int ccw(P& a, P& b, P& c);
	bool check(Vector2 a, Vector2 b, Vector2 c, Vector2 d);
}