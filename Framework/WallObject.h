#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
class WallObject :
	public GameObject
{
public:
	WallObject();
public:
	AABBCollider wallcol;
	Vector2 lefttop;
	Vector2 rightbottom;
public:
	void Update();
};

