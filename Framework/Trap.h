#pragma once
#include "GameObject.h"
#include "TriangleCollider.h"
#include "AABBCollider.h"
class Trap :
	public GameObject
{
public:
	Trap();
public:
	TriangleCollider* col;
public:
	~Trap();
};
