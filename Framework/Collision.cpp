#include "stdafx.h"
#include "Collision.h"
#include "Collider.h"
#include <math.h>

bool Collision::Intersected(const Collider::AABBBox& a, const Collider::AABBBox& b)
{
	//절대 교차할 수 없는 경우를 구한 후, 그 역을 반환
	return !(
		(a.rightBottom.x < b.leftTop.x) ||
		(b.rightBottom.x < a.leftTop.x) ||
		(a.rightBottom.y < b.leftTop.y) ||
		(b.rightBottom.y < a.leftTop.y));
}

bool Collision::Intersected(const Collider::AABBBox& a, const Collider::Circle& b)
{
	Vector2 circleDistance;
	circleDistance.x = (a.rightBottom.x + a.leftTop.x) * 0.5f - b.center.x;
	circleDistance.y = (a.rightBottom.y + a.leftTop.y) * 0.5f - b.center.y;
	Vector2 halfBox = Vector2((a.rightBottom - a.leftTop)*0.5f);

	circleDistance.x *= (circleDistance.x >= 0) ? 1.0f : -1.0f;
	circleDistance.y *= (circleDistance.y >= 0) ? 1.0f : -1.0f;

	if (circleDistance.x > (halfBox.x + b.radius)) { return false; }
	if (circleDistance.y > (halfBox.y + b.radius)) { return false; }

	if (circleDistance.x <= halfBox.x) { return true; }
	if (circleDistance.y <= halfBox.y) { return true; }

	Vector2 corner = circleDistance - halfBox;

	return (corner.DotProduct(corner) <= (b.radius * b.radius));
}

bool Collision::Intersected(const Collider::Circle& a, const Collider::Circle& b)
{
	Vector2 centerVector = b.center - a.center;					//중심을 잇는 벡터
	float distance = centerVector.DotProduct(centerVector);		//자기 자신의 내적==제곱
	return distance < ((a.radius + b.radius) * (a.radius + b.radius));	//거리비교
}

bool Collision::Intersected(const Collider::AABBBox& a, const Vector2& b)
{
	return a.leftTop.x<b.x && a.rightBottom.x>b.x &&
		a.leftTop.y<b.y && a.rightBottom.y>b.y;
}

bool Collision::Intersected(const Collider::Circle& a, const Vector2& b)
{
	Vector2 v = b - a.center;
	return v.DotProduct(v) <= a.radius*a.radius;
}

bool Collision::Intersected(const Collider::Circle& a, const Collider::Triangle& b)
{
	// 오류...
	if (Intersected(a, b.top) || Intersected(a, b.left) || Intersected(a, b.right))
		return true;
	if (abs(a.center.x * (b.left.y - b.top.y) / (b.left.x - b.top.x) + -a.center.y - a.center.x + a.center.y) /
		sqrt((b.left.y - b.top.y) / (b.left.x - b.top.x) + 1) <= a.radius)
		return true;
	else if (min(pow(a.center.x - b.top.x, 2) + pow(a.center.y - b.top.y, 2), pow(a.center.x - b.left.x, 2) + pow(a.center.y - b.left.y, 2)) < pow(a.radius, 2))
		return true;
	if (abs(a.center.x * (b.right.y - b.left.y) / (b.right.x - b.left.x) + -a.center.y - a.center.x + a.center.y) /
		sqrt((b.right.y - b.left.y) / (b.right.x - b.left.x) + 1) <= a.radius)
		return true;
	else if (min(pow(a.center.x - b.left.x, 2) + pow(a.center.y - b.left.y, 2), pow(a.center.x - b.right.x, 2) + pow(a.center.y - b.right.y, 2)) < pow(a.radius, 2))
		return true;
	if (abs(a.center.x * (b.top.y - b.right.y) / (b.top.x - b.right.x) + -a.center.y - a.center.x + a.center.y) /
		sqrt((b.top.y - b.right.y) / (b.top.x - b.right.x) + 1) <= a.radius)
		return true;
	else if (min(pow(a.center.x - b.right.x, 2) + pow(a.center.y - b.right.y, 2), pow(a.center.x - b.top.x, 2) + pow(a.center.y - b.top.y, 2)) < pow(a.radius, 2))
		return true;
	return false;
}

bool Collision::Intersected(const Collider::Triangle& a, const Collider::AABBBox& b)
{
	Vector2 leftBottom, rightTop;
	leftBottom.SetVector(b.leftTop.x, b.rightBottom.y);
	rightTop.SetVector(b.rightBottom.x, b.leftTop.y);

	return (check(a.top, a.left, b.leftTop, leftBottom) ||
		check(a.top, a.left, leftBottom, b.rightBottom) ||
		check(a.top, a.left, b.rightBottom, rightTop) ||
		check(a.top, a.left, rightTop, b.leftTop) ||

		check(a.left, a.right, b.leftTop, leftBottom) ||
		check(a.left, a.right, leftBottom, b.rightBottom) ||
		check(a.left, a.right, b.rightBottom, rightTop) ||
		check(a.left, a.right, rightTop, b.leftTop) ||

		check(a.right, a.top, b.leftTop, leftBottom) ||
		check(a.right, a.top, leftBottom, b.rightBottom) ||
		check(a.right, a.top, b.rightBottom, rightTop) ||
		check(a.right, a.top, rightTop, b.leftTop));
}

int Collision::ccw(P& a, P& b, P& c)
{
	float res = a.first * b.second + b.first * c.second + c.first * a.second;
	res -= b.first * a.second + c.first * b.second + a.first * c.second;
	if (res > 0)
		return 1;
	if (res)
		return -1;
	return 0;
}

bool Collision::check(Vector2 a, Vector2 b, Vector2 c, Vector2 d) {
	P pa = { a.x, a.y }, pb = { b.x, b.y }, pc = { c.x, c.y }, pd = { d.x, d.y };
	int ab = ccw(pa, pb, pc) * ccw(pa, pb, pd);
	int cd = ccw(pc, pd, pa) * ccw(pc, pd, pb);
	if (ab == 0 && cd == 0) {
		if (pb < pa) {
			return pc <= pa && pb <= pd;
		}
		if (pd < pc) {
			return pd <= pb && pa <= pc;
		}
		return pc <= pb && pa <= pd;
	}
	return ab <= 0 && cd <= 0;
}