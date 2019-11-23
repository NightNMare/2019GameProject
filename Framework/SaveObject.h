#pragma once
#include "GameObject.h"
#include "AABBCollider.h"
class SaveObject :
	public GameObject
{
public:
	SaveObject();
	AABBCollider col;
	Vector2 pos;
	int savenum;
	~SaveObject();
};

