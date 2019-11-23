#pragma once
#include "AABBCollider.h"
#include "CircleCollider.h"
#include "TriangleCollider.h"
#include <utility>

//충돌을 처리할 함수의 모음입니다.
//Collider가 없어도 임의로 충돌 계산이 가능합니다.
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