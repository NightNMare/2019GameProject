#include "stdafx.h"
#include "Trap.h"
#include "Framework.h"

Trap::Trap() : GameObject(L"trap.png") {
	Vector2 top, left, right;
	top.SetVector(transform->position.x, transform->position.y - 16.0f);
	left.SetVector(transform->position.x - 16.0f, transform->position.y + 16.0f);
	right.SetVector(transform->position.x + 16.0f, transform->position.y + 16.0f);
	col = new TriangleCollider(*transform, top, left, right);
}


Trap::~Trap()
{
	SAFE_DELETE(col);
}


